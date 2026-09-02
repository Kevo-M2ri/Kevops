// db.js
// SQLite is used here so the whole backend runs with zero external services -
// swap for Postgres in production by replacing this file; the schema below
// maps directly onto the data model in the backend architecture doc.

const Database = require("better-sqlite3");
const path = require("path");

const db = new Database(path.join(__dirname, "..", "council.db"));
db.pragma("journal_mode = WAL");
db.pragma("foreign_keys = ON");

db.exec(`
CREATE TABLE IF NOT EXISTS users (
  id TEXT PRIMARY KEY,
  created_at INTEGER NOT NULL,
  last_active_at INTEGER NOT NULL,
  flag_score INTEGER NOT NULL DEFAULT 0,
  subscription_status TEXT NOT NULL DEFAULT 'free',
  region TEXT
);

CREATE TABLE IF NOT EXISTS questions (
  id TEXT PRIMARY KEY,
  author_id TEXT NOT NULL,
  text TEXT NOT NULL,
  category TEXT,
  status TEXT NOT NULL DEFAULT 'active', -- active | closed | held_for_review | deleted
  created_at INTEGER NOT NULL,
  last_activity_at INTEGER NOT NULL,
  response_count INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (author_id) REFERENCES users(id)
);

CREATE TABLE IF NOT EXISTS responses (
  id TEXT PRIMARY KEY,
  question_id TEXT NOT NULL,
  responder_id TEXT NOT NULL,
  text TEXT NOT NULL,
  sentiment_score REAL,
  constructiveness_score REAL,
  status TEXT NOT NULL DEFAULT 'visible', -- visible | held_for_review | removed
  created_at INTEGER NOT NULL,
  FOREIGN KEY (question_id) REFERENCES questions(id),
  FOREIGN KEY (responder_id) REFERENCES users(id)
);

CREATE TABLE IF NOT EXISTS flags (
  id TEXT PRIMARY KEY,
  target_type TEXT NOT NULL, -- question | response
  target_id TEXT NOT NULL,
  category TEXT NOT NULL,    -- e.g. crisis_signal, spam, harassment
  tier TEXT NOT NULL,        -- A (safety-critical) | B (policy violation)
  confidence_score REAL NOT NULL,
  decided_by TEXT,           -- 'auto' or a reviewer id
  decision TEXT,             -- approve | remove | escalate | null (pending)
  decided_at INTEGER,
  appeal_status TEXT NOT NULL DEFAULT 'none',
  created_at INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS syntheses (
  id TEXT PRIMARY KEY,
  question_id TEXT NOT NULL,
  generated_at INTEGER NOT NULL,
  response_count_at_generation INTEGER NOT NULL,
  lean TEXT NOT NULL,        -- for | against | split
  for_pct INTEGER NOT NULL,
  against_pct INTEGER NOT NULL,
  mixed_pct INTEGER NOT NULL,
  highlight_for_id TEXT,
  highlight_against_id TEXT,
  FOREIGN KEY (question_id) REFERENCES questions(id)
);

CREATE TABLE IF NOT EXISTS audit_log (
  id TEXT PRIMARY KEY,
  actor_id TEXT NOT NULL,
  action TEXT NOT NULL,
  target_type TEXT NOT NULL,
  target_id TEXT NOT NULL,
  reason TEXT,
  timestamp INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS feature_flags (
  key TEXT PRIMARY KEY,
  enabled INTEGER NOT NULL DEFAULT 1,
  value TEXT,
  updated_by TEXT,
  updated_at INTEGER NOT NULL
);
`);

module.exports = db;
