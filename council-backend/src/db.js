// db.js
// SQLite is used here so the whole backend runs with zero external services -
// swap for Postgres in production by replacing this file; the schema below
// maps directly onto the data model in the backend architecture doc.
//
// NOTE: this schema changed to add auth, confessions, reply threading, and
// data-retention controls. If you have an existing local council.db from
// before, delete it and re-run `npm run seed:flags` - SQLite doesn't add
// new columns to an already-created table automatically.

const Database = require("better-sqlite3");
const path = require("path");

const db = new Database(path.join(__dirname, "..", "council.db"));
db.pragma("journal_mode = WAL");
db.pragma("foreign_keys = ON");

db.exec(`
CREATE TABLE IF NOT EXISTS users (
  id TEXT PRIMARY KEY,
  email TEXT UNIQUE,
  password_hash TEXT,
  created_at INTEGER NOT NULL,
  last_active_at INTEGER NOT NULL,
  flag_score INTEGER NOT NULL DEFAULT 0,
  subscription_status TEXT NOT NULL DEFAULT 'free',
  first_question_at INTEGER,   -- when their free month of asking questions started
  region TEXT
);

CREATE TABLE IF NOT EXISTS sessions (
  token TEXT PRIMARY KEY,
  user_id TEXT NOT NULL,
  created_at INTEGER NOT NULL,
  FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE IF NOT EXISTS questions (
  id TEXT PRIMARY KEY,
  author_id TEXT,             -- NULL for confessions: never linked to an identity, on purpose
  kind TEXT NOT NULL DEFAULT 'question', -- question | confession
  text TEXT NOT NULL,
  category TEXT,
  status TEXT NOT NULL DEFAULT 'active', -- active | closed | held_for_review | deleted
  retain INTEGER NOT NULL DEFAULT 0,     -- 1 = author asked to keep this past the normal window
  created_at INTEGER NOT NULL,
  last_activity_at INTEGER NOT NULL,
  response_count INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (author_id) REFERENCES users(id)
);

CREATE TABLE IF NOT EXISTS responses (
  id TEXT PRIMARY KEY,
  question_id TEXT NOT NULL,
  responder_id TEXT,          -- nullable: set to NULL when the responder deletes their data
  parent_response_id TEXT,    -- NULL = direct reply to the question; otherwise a reply to another response
  text TEXT NOT NULL,
  status TEXT NOT NULL DEFAULT 'visible', -- visible | held_for_review | removed
  created_at INTEGER NOT NULL,
  FOREIGN KEY (question_id) REFERENCES questions(id),
  FOREIGN KEY (responder_id) REFERENCES users(id),
  FOREIGN KEY (parent_response_id) REFERENCES responses(id)
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

CREATE TABLE IF NOT EXISTS audit_log (
  id TEXT PRIMARY KEY,
  actor_id TEXT NOT NULL,
  action TEXT NOT NULL,
  target_type TEXT NOT NULL,
  target_id TEXT NOT NULL,
  reason TEXT,
  timestamp INTEGER NOT NULL
);

-- What's left after someone deletes their account data: no text, no author
-- link, no question/response ids - just enough to keep aggregate product
-- analytics (e.g. "how many career questions get asked per week") honest.
CREATE TABLE IF NOT EXISTS deleted_account_stats (
  id TEXT PRIMARY KEY,
  category TEXT,
  kind TEXT,
  response_count INTEGER,
  original_created_at INTEGER,
  deleted_at INTEGER NOT NULL
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
