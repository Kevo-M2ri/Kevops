const express = require("express");
const crypto = require("crypto");
const db = require("../db");
const { moderate, CRISIS_RESOURCE_MESSAGE } = require("../moderation");

function questionsRouter() {
  const router = express.Router();

  // POST /api/questions
  router.post("/", (req, res) => {
    const { author_id, text, category } = req.body || {};
    if (!author_id || !text) {
      return res.status(400).json({ error: "author_id and text are required" });
    }

    const check = moderate(text);
    const now = Date.now();
    const id = crypto.randomUUID();
    const status = check.tier ? "held_for_review" : "active";

    db.prepare(
      `INSERT INTO questions (id, author_id, text, category, status, created_at, last_activity_at, response_count)
       VALUES (@id, @author_id, @text, @category, @status, @now, @now, 0)`
    ).run({ id, author_id, text, category: category || "other", status, now });

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

    const response = { id, status };
    if (check.tier === "A") response.crisis_message = CRISIS_RESOURCE_MESSAGE;
    if (check.tier === "B") response.message = "Your question is being reviewed before it's shown to responders.";
    res.status(201).json(response);
  });

  // GET /api/questions/:id
  router.get("/:id", (req, res) => {
    const question = db.prepare(`SELECT * FROM questions WHERE id = ?`).get(req.params.id);
    if (!question) return res.status(404).json({ error: "not found" });

    const responses = db
      .prepare(
        `SELECT id, text, sentiment_score, constructiveness_score, created_at
         FROM responses WHERE question_id = ? AND status = 'visible'
         ORDER BY created_at DESC LIMIT 20`
      )
      .all(req.params.id);

    const synthesis = db
      .prepare(`SELECT * FROM syntheses WHERE question_id = ? ORDER BY generated_at DESC LIMIT 1`)
      .get(req.params.id);

    res.json({ question, recent_responses: responses, synthesis: synthesis || null });
  });

  return router;
}

module.exports = questionsRouter;
