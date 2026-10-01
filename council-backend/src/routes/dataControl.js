const express = require("express");
const crypto = require("crypto");
const db = require("../db");
const { requireAuth } = require("../auth");

function dataControlRouter() {
  const router = express.Router();

  // PATCH /api/questions/:id/retain   { retain: true|false }
  // Lets the asker keep a question past the normal retention window (see
  // the retention sweep job), or put it back on the normal schedule.
  router.patch("/questions/:id/retain", requireAuth, (req, res) => {
    const question = db.prepare(`SELECT * FROM questions WHERE id = ?`).get(req.params.id);
    if (!question) return res.status(404).json({ error: "not found" });
    if (question.author_id !== req.userId) {
      return res.status(403).json({ error: "You can only manage retention on your own questions." });
    }
    const retain = req.body && req.body.retain ? 1 : 0;
    db.prepare(`UPDATE questions SET retain = ? WHERE id = ?`).run(retain, question.id);
    res.json({ id: question.id, retain: !!retain });
  });

  // DELETE /api/users/me/data
  // Deletes everything that identifies this person: their asked questions
  // (and every response under them), and scrubs their identity + wording
  // from any response they left on someone else's question (the row stays,
  // so replies to it don't break, but it becomes untraceable to them).
  // What's kept afterward is a handful of anonymized aggregate rows -
  // category, kind, response count, timestamps - with no text and no link
  // back to the account. That's the "only useful data remains" line drawn
  // in code: useful means aggregate and anonymous, nothing else survives.
  router.delete("/users/me/data", requireAuth, (req, res) => {
    const userId = req.userId;
    const now = Date.now();

    const ownedQuestions = db.prepare(`SELECT * FROM questions WHERE author_id = ?`).all(userId);

    const tx = db.transaction(() => {
      for (const q of ownedQuestions) {
        db.prepare(
          `INSERT INTO deleted_account_stats (id, category, kind, response_count, original_created_at, deleted_at)
           VALUES (?, ?, ?, ?, ?, ?)`
        ).run(crypto.randomUUID(), q.category, q.kind, q.response_count, q.created_at, now);

        db.prepare(`DELETE FROM flags WHERE target_type = 'response' AND target_id IN (SELECT id FROM responses WHERE question_id = ?)`).run(q.id);
        db.prepare(`DELETE FROM responses WHERE question_id = ?`).run(q.id);
        db.prepare(`DELETE FROM flags WHERE target_type = 'question' AND target_id = ?`).run(q.id);
        db.prepare(`DELETE FROM questions WHERE id = ?`).run(q.id);
      }

      // Scrub (not delete the row - that would break reply threads) any
      // response this person left anywhere else.
      db.prepare(
        `UPDATE responses SET text = '[deleted]', responder_id = NULL WHERE responder_id = ?`
      ).run(userId);

      db.prepare(`DELETE FROM sessions WHERE user_id = ?`).run(userId);
      db.prepare(`DELETE FROM users WHERE id = ?`).run(userId);
    });

    tx();
    res.json({ deleted: true, questions_removed: ownedQuestions.length });
  });

  return router;
}

module.exports = dataControlRouter;
