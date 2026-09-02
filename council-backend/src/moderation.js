// moderation.js
//
// This is a deliberately simple, transparent stand-in for a real moderation
// system. It exists so the request pipeline (hold -> flag -> review) can be
// built and tested end-to-end now. Before real users touch this platform,
// replace `moderate()` with a call to a proper classification service -
// see the moderation design doc, Sections 2-3, for the categories this
// needs to cover and why keyword matching alone is not sufficient for
// anything nuanced (sarcasm, coded language, context-dependent harassment).
//
// Tier A = safety-critical (routes to crisis resources, held from publish
//          pending human confirmation).
// Tier B = policy violation (held from publish, goes to the review queue).

const CRISIS_PATTERNS = [
  /kill myself/i,
  /end my life/i,
  /want to die/i,
  /suicid/i,
  /self[- ]harm/i,
  /hurt myself/i,
];

const VIOLATION_PATTERNS = [
  { category: "spam", pattern: /https?:\/\//i, confidence: 0.6 },
  { category: "spam", pattern: /\b(buy now|click here|dm me for)\b/i, confidence: 0.7 },
  { category: "harassment", pattern: /\b(kill yourself|you're worthless|nobody likes you)\b/i, confidence: 0.85 },
];

/**
 * @param {string} text
 * @returns {{ tier: 'A'|'B'|null, category: string|null, confidence: number }}
 */
function moderate(text) {
  for (const pattern of CRISIS_PATTERNS) {
    if (pattern.test(text)) {
      return { tier: "A", category: "crisis_signal", confidence: 0.9 };
    }
  }
  for (const { category, pattern, confidence } of VIOLATION_PATTERNS) {
    if (pattern.test(text)) {
      return { tier: "B", category, confidence };
    }
  }
  return { tier: null, category: null, confidence: 0 };
}

// Shown to a user immediately when a Tier A signal is detected - this is a
// starting point only. Section 5 of the moderation doc requires sign-off
// from a licensed mental health professional before this copy or flow
// ships to real users.
const CRISIS_RESOURCE_MESSAGE =
  "It sounds like you might be going through something really difficult. " +
  "If you're in the US, you can call or text 988 (Suicide & Crisis Lifeline) " +
  "any time. If you're elsewhere, findahelpline.com can point you to a local " +
  "resource. Your question has been held so a person can check in on it first.";

module.exports = { moderate, CRISIS_RESOURCE_MESSAGE };
