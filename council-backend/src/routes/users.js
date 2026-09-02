const express = require("express");
const crypto = require("crypto");
const db = require("../db");

function usersRouter() {
  const router = express.Router();

  // POST /api/users  { region }
  // Creates a pseudonymous account. Real auth (email/OAuth) would sit in
  // front of this and store its own hashed reference separately, per the
  // backend architecture doc's note on keeping auth_ref split from profile data.
  router.post("/", (req, res) => {
    const { region } = req.body || {};
    const id = crypto.randomUUID();
    const now = Date.now();
    db.prepare(
      `INSERT INTO users (id, created_at, last_active_at, region) VALUES (?, ?, ?, ?)`
    ).run(id, now, now, region || null);
    res.status(201).json({ id });
  });

  return router;
}

module.exports = usersRouter;
