const express = require("express");
const crypto = require("crypto");
const db = require("../db");
const { moderate, CRISIS_RESOURCE_MESSAGE } = require("../moderation");
const { requireAuth } = require("../auth");

const TRIAL_DAYS = 30;

function questionsRouter() {
  const router = express.Router();

  // POST /api/questions   { text, category, kind }
  // Requires a signed-in account - both questions and confessions do.
  // kind: 'question' (default) or 'confession'.
  //
  // For confessions, author_id is deliberately never stored: the person
  // must be signed in (so moderation/abuse content checks still apply and
  // spam is harder), but once the content is written down, nothing in the
  // database links it back to who wrote it - not even to us. The trade-off
  // is real: we can't apply the usual repeat-offender flag_score tracking
  // to confessions specifically, only to questions and responses. That's
  // an intentional privacy-over-tracking choice, not an oversight.
  router.post("/", requireAuth, (req, res) => {
    const { text, category, kind } = req.body || {};
    if (!text) return res.status(400).json({ error: "text is required" });
    const questionKind = kind === "confession" ? "confession" : "question";

    const user = db.prepare(`SELECT * FROM users WHERE id = ?`).get(req.userId);
    if (!user) return res.status(401).json({ error: "Sign in required." });

    // Paywall: only applies to questions, not confessions or responses.
    // First question ever starts a 30-day free window; after that, asking
    // another question requires an active subscription. (No real billing
    // is wired up yet - see the pricing design doc - this is the gate a
    // real payment flow would sit behind.)
    if (questionKind === "question") {
      const now = Date.now();
      if (!user.first_question_at) {
        db.prepare(`UPDATE users SET first_question_at = ? WHERE id = ?`).run(now, user.id);
      } else {
        const trialEnds = user.first_question_at + TRIAL_DAYS * 24 * 60 * 60 * 1000;
        if (now > trialEnds && user.subscription_status !== "active") {
          return res.status(402).json({
            error: "Your first free month of asking questions has ended. Subscribing keeps this open.",
            code: "trial_expired",
          });
        }
      }
    }

    const check = moderate(text);
    const now = Date.now();
    const id = crypto.randomUUID();
    const status = check.tier ? "held_for_review" : "active";
    const authorId = questionKind === "confession" ? null : user.id;

    db.prepare(
      `INSERT INTO questions (id, author_id, kind, text, category, status, created_at, last_activity_at, response_count)
       VALUES (@id, @author_id, @kind, @text, @category, @status, @now, @now, 0)`
    ).run({ id, author_id: authorId, kind: questionKind, text, category: category || "other", status, now });

    if (check.tier) {
      db.prepare(
        `INSERT INTO flags (id, target_type, target_id, category, tier, confidence_score, created_at)
         VALUES (@id, 'question', @target_id, @category, @tier, @confidence, @now)`
      ).run({
        id: crypto.randomUUID(),
        target_id: id,
        category: check.category,
        tier: check.tier,
        confidence: check.confidence,
        now,
      });
    }

    const response = { id, status, kind: questionKind };
    if (check.tier === "A") response.crisis_message = CRISIS_RESOURCE_MESSAGE;
    if (check.tier === "B") response.message = "This is being reviewed before it's shown to anyone.";
    res.status(201).json(response);
  });

  // GET /api/questions?kind=confession
  // A public feed so confessions can actually be discovered and read, not
  // just accessed via a direct link. Never selects author_id - it doesn't
  // exist for confessions, and this keeps that true architecturally, not
  // just by convention in one query.
  router.get("/", (req, res) => {
    if (req.query.kind !== "confession") {
      return res.status(400).json({ error: "only ?kind=confession is supported as a public feed" });
    }
    const rows = db
      .prepare(
        `SELECT id, text, created_at FROM questions
         WHERE kind = 'confession' AND status = 'active'
         ORDER BY created_at DESC LIMIT 50`
      )
      .all();
    res.json({ confessions: rows });
  });

  // GET /api/questions/:id
  // Never returns author_id, for either questions or confessions - reading
  // and answering never needs to know who asked.
  router.get("/:id", (req, res) => {
    const question = db
      .prepare(
        `SELECT id, kind, text, category, status, retain, created_at, last_activity_at, response_count
         FROM questions WHERE id = ?`
      )
      .get(req.params.id);
    if (!question) return res.status(404).json({ error: "not found" });

    const responses = db
      .prepare(
        `SELECT id, parent_response_id, text, created_at
         FROM responses WHERE question_id = ? AND status = 'visible'
         ORDER BY created_at ASC`
      )
      .all(req.params.id);

    res.json({ question, responses });
  });

  return router;
}

module.exports = questionsRouter;
