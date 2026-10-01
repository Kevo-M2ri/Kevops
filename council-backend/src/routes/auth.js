const express = require("express");
const crypto = require("crypto");
const db = require("../db");
const { hashPassword, verifyPassword, createSession } = require("../auth");

function authRouter() {
  const router = express.Router();

  // POST /api/auth/signup  { email, password, region }
  router.post("/signup", (req, res) => {
    const { email, password, region } = req.body || {};
    if (!email || !password || password.length < 8) {
      return res.status(400).json({ error: "A valid email and a password of at least 8 characters are required." });
    }
    const existing = db.prepare(`SELECT id FROM users WHERE email = ?`).get(email);
    if (existing) return res.status(409).json({ error: "An account with that email already exists." });

    const id = crypto.randomUUID();
    const now = Date.now();
    db.prepare(
      `INSERT INTO users (id, email, password_hash, created_at, last_active_at, region)
       VALUES (?, ?, ?, ?, ?, ?)`
    ).run(id, email, hashPassword(password), now, now, region || null);

    const token = createSession(id);
    res.status(201).json({ token, userId: id });
  });

  // POST /api/auth/login  { email, password }
  router.post("/login", (req, res) => {
    const { email, password } = req.body || {};
    const user = db.prepare(`SELECT * FROM users WHERE email = ?`).get(email);
    if (!user || !verifyPassword(password || "", user.password_hash)) {
      return res.status(401).json({ error: "Incorrect email or password." });
    }
    db.prepare(`UPDATE users SET last_active_at = ? WHERE id = ?`).run(Date.now(), user.id);
    const token = createSession(user.id);
    res.json({ token, userId: user.id });
  });

  return router;
}

module.exports = authRouter;
