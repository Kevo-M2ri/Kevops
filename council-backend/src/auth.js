// auth.js
//
// Deliberately simple, self-contained auth - no external service, no JWT
// library, just salted password hashes and opaque session tokens in the
// database. This is enough to require real accounts for questions and
// confessions while keeping the project dependency-free. Before this goes
// in front of real users, add things this doesn't do: password reset,
// email verification, rate-limiting login attempts, and session expiry.

const crypto = require("crypto");
const db = require("./db");

function hashPassword(password) {
  const salt = crypto.randomBytes(16).toString("hex");
  const hash = crypto.scryptSync(password, salt, 64).toString("hex");
  return `${salt}:${hash}`;
}

function verifyPassword(password, stored) {
  if (!stored) return false;
  const [salt, hash] = stored.split(":");
  const check = crypto.scryptSync(password, salt, 64).toString("hex");
  const a = Buffer.from(hash, "hex");
  const b = Buffer.from(check, "hex");
  return a.length === b.length && crypto.timingSafeEqual(a, b);
}

function createSession(userId) {
  const token = crypto.randomUUID();
  db.prepare(`INSERT INTO sessions (token, user_id, created_at) VALUES (?, ?, ?)`).run(
    token,
    userId,
    Date.now()
  );
  return token;
}

function getUserIdForToken(token) {
  if (!token) return null;
  const row = db.prepare(`SELECT user_id FROM sessions WHERE token = ?`).get(token);
  return row ? row.user_id : null;
}

function extractToken(req) {
  const header = req.headers.authorization || "";
  const match = header.match(/^Bearer (.+)$/);
  return match ? match[1] : null;
}

/** Requires a valid session. 401s if missing/invalid. */
function requireAuth(req, res, next) {
  const userId = getUserIdForToken(extractToken(req));
  if (!userId) return res.status(401).json({ error: "Sign in required." });
  req.userId = userId;
  next();
}

/** Attaches req.userId if a valid session is present; never blocks the request. */
function optionalAuth(req, res, next) {
  req.userId = getUserIdForToken(extractToken(req)) || null;
  next();
}

module.exports = { hashPassword, verifyPassword, createSession, requireAuth, optionalAuth };
