const express = require("express");
const crypto = require("crypto");
const db = require("../db");
const { moderate, CRISIS_RESOURCE_MESSAGE } = require("../moderation");
const { getFlagInt } = require("../featureFlags");
const { optionalAuth } = require("../auth");

function responsesRouter(broadcast) {
  const router = express.Router();

  // POST /api/questions/:id/responses   { text, parent_id, responder_id }
  // Answering never requires an account. If the person is signed in
  // (Authorization header), we use that identity internally for abuse
  // control; otherwise a client-supplied pseudonymous responder_id is
  // used (see POST /api/users), matching "reading and answering doesn't
  // need an account unless you want one."
  router.post("/:id/responses", optionalAuth, (req, res) => {
    const questionId = req.params.id;
    const { text, parent_id } = req.body || {};
    const responderId = req.userId || req.body.responder_id;
    if (!responderId || !text) {
      return res.status(400).json({ error: "text is required, and either be signed in or include responder_id" });
    }

    const question = db.prepare(`SELECT * FROM questions WHERE id = ?`).get(questionId);
    if (!question) return res.status(404).json({ error: "question not found" });
    if (question.status !== "active") {
      return res.status(409).json({ error: `question is ${question.status}, not accepting responses` });
    }

    let parentResponseId = null;
    if (parent_id) {
      const parent = db
        .prepare(`SELECT id FROM responses WHERE id = ? AND question_id = ? AND status = 'visible'`)
        .get(parent_id, questionId);
      if (!parent) return res.status(400).json({ error: "parent_id does not refer to a visible response on this question" });
      parentResponseId = parent.id;
    }

    const check = moderate(text);
    const now = Date.now();
    const id = crypto.randomUUID();

    if (check.tier) {
      db.prepare(
        `INSERT INTO responses (id, question_id, responder_id, parent_response_id, text, status, created_at)
         VALUES (@id, @question_id, @responder_id, @parent_response_id, @text, 'held_for_review', @now)`
      ).run({ id, question_id: questionId, responder_id: responderId, parent_response_id: parentResponseId, text, now });

      db.prepare(
        `INSERT INTO flags (id, target_type, target_id, category, tier, confidence_score, created_at)
         VALUES (@id, 'response', @target_id, @category, @tier, @confidence, @now)`
      ).run({
        id: crypto.randomUUID(),
        target_id: id,
        category: check.category,
        tier: check.tier,
        confidence: check.confidence,
        now,
      });

      const body = { id, status: "held_for_review" };
      if (check.tier === "A") body.crisis_message = CRISIS_RESOURCE_MESSAGE;
      return res.status(202).json(body);
    }

    db.prepare(
      `INSERT INTO responses (id, question_id, responder_id, parent_response_id, text, status, created_at)
       VALUES (@id, @question_id, @responder_id, @parent_response_id, @text, 'visible', @now)`
    ).run({ id, question_id: questionId, responder_id: responderId, parent_response_id: parentResponseId, text, now });

    const updated = db
      .prepare(
        `UPDATE questions SET response_count = response_count + 1, last_activity_at = ? WHERE id = ?
         RETURNING response_count`
      )
      .get(now, questionId);
    const responseCount = updated.response_count;

    const responsePayload = { id, parent_response_id: parentResponseId, text, created_at: now };
    broadcast(questionId, { type: "response", response: responsePayload, response_count: responseCount });

    const threshold = getFlagInt("notification_threshold", 100);
    if (responseCount === threshold) {
      broadcast(questionId, { type: "notification", message: `${threshold} people have responded.` });
    }

    res.status(201).json({ id, parent_response_id: parentResponseId, status: "visible", response_count: responseCount });
  });

  return router;
}

module.exports = responsesRouter;
