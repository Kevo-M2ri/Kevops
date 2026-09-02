// retentionSweep.js
//
// Run on a schedule (e.g. daily via cron) in production. Hard-deletes
// questions (and their responses) that have had no activity within the
// retention window, per product spec Section 4.1 / backend architecture
// Section 4. This does NOT touch encrypted backups - see backend
// architecture doc Section 9.3, which flags that as a separate, still-open
// policy decision.

const db = require("../db");
const { getFlagInt } = require("../featureFlags");

function runRetentionSweep({ now = Date.now() } = {}) {
  const retentionDays = getFlagInt("retention_days", 60);
  const cutoff = now - retentionDays * 24 * 60 * 60 * 1000;

  const expired = db
    .prepare(`SELECT id FROM questions WHERE last_activity_at < ? AND status != 'deleted'`)
    .all(cutoff);

  const deleteResponses = db.prepare(`DELETE FROM responses WHERE question_id = ?`);
  const deleteQuestion = db.prepare(`DELETE FROM questions WHERE id = ?`);
  const deleteFlags = db.prepare(`DELETE FROM flags WHERE target_id = ?`);

  const tx = db.transaction((questionIds) => {
    for (const qid of questionIds) {
      deleteResponses.run(qid);
      deleteFlags.run(qid);
      deleteQuestion.run(qid);
    }
  });

  tx(expired.map((q) => q.id));
  return { deleted_count: expired.length, retention_days: retentionDays };
}

// Also exposed as a standalone script: `npm run sweep`
if (require.main === module) {
  const result = runRetentionSweep();
  console.log(`Retention sweep complete: ${result.deleted_count} question(s) deleted (retention window: ${result.retention_days} days).`);
}

module.exports = { runRetentionSweep };
