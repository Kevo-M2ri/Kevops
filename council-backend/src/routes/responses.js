const express = require("express");
const crypto = require("crypto");
const db = require("../db");
const { moderate, CRISIS_RESOURCE_MESSAGE } = require("../moderation");
const { scoreSentiment, scoreConstructiveness, generateSynthesis } = require("../ai");
const { getFlagInt } = require("../featureFlags");

function responsesRouter(broadcast) {
  const router = express.Router();

  // POST /api/questions/:id/responses
  router.post("/:id/responses", (req, res) => {
    const questionId = req.params.id;
    const { responder_id, text } = req.body || {};
    if (!responder_id || !text) {
      return res.status(400).json({ error: "responder_id and text are required" });
    }

    const question = db.prepare(`SELECT * FROM questions WHERE id = ?`).get(questionId);
    if (!question) return res.status(404).json({ error: "question not found" });
    if (question.status !== "active") {
      return res.status(409).json({ error: `question is ${question.status}, not accepting responses` });
    }

    const check = moderate(text);
    const now = Date.now();
    const id = crypto.randomUUID();

    if (check.tier) {
      const status = "held_for_review";
      db.prepare(
        `INSERT INTO responses (id, question_id, responder_id, text, status, created_at)
         VALUES (@id, @question_id, @responder_id, @text, @status, @now)`
      ).run({ id, question_id: questionId, responder_id, text, status, now });

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

      const body = { id, status };
      if (check.tier === "A") body.crisis_message = CRISIS_RESOURCE_MESSAGE;
      return res.status(202).json(body);
    }

    const sentiment_score = scoreSentiment(text);
    const constructiveness_score = scoreConstructiveness(text);

    db.prepare(
      `INSERT INTO responses (id, question_id, responder_id, text, sentiment_score, constructiveness_score, status, created_at)
       VALUES (@id, @question_id, @responder_id, @text, @sentiment_score, @constructiveness_score, 'visible', @now)`
    ).run({ id, question_id: questionId, responder_id, text, sentiment_score, constructiveness_score, now });

    const updated = db
      .prepare(
        `UPDATE questions SET response_count = response_count + 1, last_activity_at = ? WHERE id = ?
         RETURNING response_count`
      )
      .get(now, questionId);
    const responseCount = updated.response_count;

    const responsePayload = { id, text, sentiment_score, constructiveness_score, created_at: now };

    broadcast(questionId, { type: "response", response: responsePayload, response_count: responseCount });

    const threshold = getFlagInt("notification_threshold", 100);
    let synthesis = null;
    if (responseCount === threshold) {
      const visibleResponses = db
        .prepare(
          `SELECT id, text, sentiment_score, constructiveness_score FROM responses
           WHERE question_id = ? AND status = 'visible'`
        )
        .all(questionId);

      const result = generateSynthesis(visibleResponses);
      const synthesisId = crypto.randomUUID();

      db.prepare(
        `INSERT INTO syntheses (id, question_id, generated_at, response_count_at_generation, lean, for_pct, against_pct, mixed_pct, highlight_for_id, highlight_against_id)
         VALUES (@id, @question_id, @now, @count, @lean, @forPct, @againstPct, @mixedPct, @highlightForId, @highlightAgainstId)`
      ).run({ id: synthesisId, question_id: questionId, now, count: responseCount, ...result });

      synthesis = { id: synthesisId, ...result };
      broadcast(questionId, { type: "notification", message: `${threshold} voices have spoken - your verdict is ready.` });
      broadcast(questionId, { type: "synthesis", synthesis });
    }

    res.status(201).json({ id, status: "visible", sentiment_score, constructiveness_score, response_count: responseCount, synthesis });
  });

  return router;
}

module.exports = responsesRouter;
