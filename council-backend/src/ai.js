// ai.js
//
// Stand-in for the real AI sorting pipeline described in the product spec
// (Section 5). This uses simple keyword heuristics so the rest of the
// system - live tally, convergence marker, synthesis panel, notification
// threshold - can be built and demoed without an external AI dependency.
// Swap `scoreSentiment` and `scoreConstructiveness` for real model calls
// when ready; keep the function signatures the same and nothing else in
// the app needs to change.

const POSITIVE_WORDS = [
  "should", "trust", "go", "worth", "support", "yes", "agree", "confident",
  "jump", "ready", "clearly", "regret", "outgrown",
];
const NEGATIVE_WORDS = [
  "stay", "risk", "careful", "against", "no", "wait", "concern", "burnout",
  "debt", "slow", "plan", "honestly",
];

function clamp(n, min, max) {
  return Math.max(min, Math.min(max, n));
}

/** Returns a score from -1 (strongly against) to +1 (strongly for). */
function scoreSentiment(text) {
  const lower = text.toLowerCase();
  let score = 0;
  for (const w of POSITIVE_WORDS) if (lower.includes(w)) score += 0.18;
  for (const w of NEGATIVE_WORDS) if (lower.includes(w)) score -= 0.18;
  return clamp(score, -1, 1);
}

/** Returns a score from 0 to 1 - how specific/reasoned the response is. */
function scoreConstructiveness(text) {
  let score = 0.25;
  if (text.length > 60) score += 0.2;
  if (/\d/.test(text)) score += 0.15;
  if (/\b(because|since|so that|if you)\b/i.test(text)) score += 0.25;
  if (text.length < 15) score -= 0.2;
  return clamp(score, 0, 1);
}

/**
 * Builds the synthesis panel data from a question's visible responses.
 * @param {Array<{id:string, text:string, sentiment_score:number, constructiveness_score:number}>} responses
 */
function generateSynthesis(responses) {
  const total = responses.length || 1;
  const forResp = responses.filter((r) => r.sentiment_score > 0.15);
  const againstResp = responses.filter((r) => r.sentiment_score < -0.15);
  const forPct = Math.round((forResp.length / total) * 100);
  const againstPct = Math.round((againstResp.length / total) * 100);
  const mixedPct = Math.max(0, 100 - forPct - againstPct);

  const rank = (list, sign) =>
    [...list].sort(
      (a, b) =>
        Math.abs(b.sentiment_score) * b.constructiveness_score -
        Math.abs(a.sentiment_score) * a.constructiveness_score
    )[0];

  const bestFor = rank(forResp, 1);
  const bestAgainst = rank(againstResp, -1);
  const lean = forPct === againstPct ? "split" : forPct > againstPct ? "for" : "against";

  return {
    lean,
    forPct,
    againstPct,
    mixedPct,
    highlightForId: bestFor ? bestFor.id : null,
    highlightAgainstId: bestAgainst ? bestAgainst.id : null,
  };
}

module.exports = { scoreSentiment, scoreConstructiveness, generateSynthesis };
