// featureFlags.js
// Small helper over the feature_flags table so both routes and jobs read
// flags the same way. See backend architecture doc, Section 7.

const db = require("./db");

const DEFAULTS = [
  { key: "notification_threshold", enabled: 1, value: "100" },
  { key: "moderation_sensitivity", enabled: 1, value: "medium" },
  { key: "ads_enabled", enabled: 1, value: "true" },
  { key: "retention_days", enabled: 1, value: "60" },
];

function ensureDefaults() {
  const insert = db.prepare(
    `INSERT OR IGNORE INTO feature_flags (key, enabled, value, updated_by, updated_at)
     VALUES (@key, @enabled, @value, 'system', @now)`
  );
  const now = Date.now();
  for (const flag of DEFAULTS) insert.run({ ...flag, now });
}

function getFlag(key) {
  return db.prepare(`SELECT * FROM feature_flags WHERE key = ?`).get(key);
}

function getFlagValue(key, fallback) {
  const row = getFlag(key);
  if (!row || !row.enabled) return fallback;
  return row.value;
}

function getFlagInt(key, fallback) {
  const v = getFlagValue(key, null);
  const n = Number(v);
  return Number.isFinite(n) ? n : fallback;
}

function listFlags() {
  return db.prepare(`SELECT * FROM feature_flags ORDER BY key`).all();
}

function setFlag(key, { enabled, value, updated_by }) {
  db.prepare(
    `INSERT INTO feature_flags (key, enabled, value, updated_by, updated_at)
     VALUES (@key, @enabled, @value, @updated_by, @now)
     ON CONFLICT(key) DO UPDATE SET
       enabled = excluded.enabled,
       value = excluded.value,
       updated_by = excluded.updated_by,
       updated_at = excluded.updated_at`
  ).run({ key, enabled: enabled ? 1 : 0, value: String(value), updated_by: updated_by || "unknown", now: Date.now() });
  return getFlag(key);
}

module.exports = { ensureDefaults, getFlag, getFlagValue, getFlagInt, listFlags, setFlag };
