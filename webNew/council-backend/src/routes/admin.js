const express = require("express");
const crypto = require("crypto");
const db = require("../db");

function adminRouter() {
  const router = express.Router();

  // GET /api/admin/flags - pending review queue
  router.get("/flags", (req, res) => {
    const flags = db
      .prepare(`SELECT * FROM flags WHERE decision IS NULL ORDER BY created_at ASC`)
      .all();
    res.json({ flags });
  });

  // POST /api/admin/flags/:id/decision  { decision: 'approve'|'remove'|'escalate', actor_id, reason }
  router.post("/flags/:id/decision", (req, res) => {
    const { decision, actor_id, reason } = req.body || {};
    if (!["approve", "remove", "escalate"].includes(decision) || !actor_id) {
      return res.status(400).json({ error: "decision (approve|remove|escalate) and actor_id are required" });
    }

    const flag = db.prepare(`SELECT * FROM flags WHERE id = ?`).get(req.params.id);
    if (!flag) return res.status(404).json({ error: "flag not found" });

    const now = Date.now();
    db.prepare(
      `UPDATE flags SET decision = ?, decided_by = ?, decided_at = ? WHERE id = ?`
    ).run(decision, actor_id, now, flag.id);

    const table = flag.target_type === "question" ? "questions" : "responses";
    const newStatus = decision === "approve" ? (flag.target_type === "question" ? "active" : "visible") : "removed";
    db.prepare(`UPDATE ${table} SET status = ? WHERE id = ?`).run(newStatus, flag.target_id);

    db.prepare(
      `INSERT INTO audit_log (id, actor_id, action, target_type, target_id, reason, timestamp)
       VALUES (@id, @actor_id, @action, @target_type, @target_id, @reason, @now)`
    ).run({
      id: crypto.randomUUID(),
      actor_id,
      action: `flag_decision:${decision}`,
      target_type: flag.target_type,
      target_id: flag.target_id,
      reason: reason || null,
      now,
    });

    res.json({ flag_id: flag.id, decision, new_status: newStatus });
  });

  return router;
}

module.exports = adminRouter;
