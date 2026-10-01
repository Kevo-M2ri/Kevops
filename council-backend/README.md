# Council — backend (reference implementation)

Real accounts, threaded replies, anonymous confessions, a 30-day free
window before questions require a subscription, and full user-controlled
data deletion. Runs on SQLite + an in-process WebSocket, zero external
services needed to try it locally.

## Run it

```bash
npm install
npm run seed:flags   # creates default feature flags (once)
npm start             # http://localhost:3000
```

## What changed in this version

- **No more sentiment/positive-negative scoring.** The old AI-sorted "chamber" visualization and synthesis panel are gone. Responses are just listed, threaded.
- **Threaded replies.** Any response can reply to another response, not just to the question. The frontend renders these nested with indentation. Backend: `responses.parent_response_id`.
- **Full-page theming.** The generated artwork now fills the entire viewport as a background, and the *entire* palette (not just an accent color) is derived from it — background, panels, borders, everything.
- **Real authentication.** `src/auth.js` — salted password hashes (Node's built-in `crypto.scrypt`, no bcrypt dependency) and opaque session tokens. **Asking a question or posting a confession requires signing in. Responding and reading never do.**
- **Confessions.** A second content type (`questions.kind = 'confession'`). Requires sign-in to post (so moderation still applies and it's harder to spam), but `author_id` is deliberately never written to the row — once posted, nothing in the database links it back to the account, not even for us to see. Read-only: no replies, no author ever shown. See the trade-off this creates below.
- **A 30-day free window.** First question ever starts the clock (`users.first_question_at`). After 30 days, asking another question returns `402` unless `subscription_status = 'active'`. No real payment processing is wired up — this is the gate a real billing integration (see the pricing design doc from earlier) would sit behind. Confessions and responses are never gated.
- **User-controlled retention.** `PATCH /api/questions/:id/retain` lets the asker exempt a question from the automatic deletion sweep. `DELETE /api/users/me/data` deletes everything identifying (their questions, the responses under them, their account) and scrubs their identity from any reply they left elsewhere — while keeping a handful of anonymized aggregate rows (category, kind, response count, no text, no ids) in `deleted_account_stats`, so basic product analytics survive without any way to trace back to a person.

## The trade-off worth knowing about

Confessions get real anonymity (verified in testing: the raw database row has `author_id = NULL`), but that means **we can't apply the usual repeat-offender tracking to confessions** the way we can for questions and responses — there's no identity to accumulate a flag score against. Content-level moderation (the crisis/spam keyword check) still runs on every confession before it publishes; what's gone is the ability to notice a pattern across someone's confessions over time. That's the actual cost of "not even the backend can see who posted it," not a bug — but worth having in mind before deciding this is the right trade-off for a public launch.

## Auth quickstart

```bash
# create an account
curl -X POST http://localhost:3000/api/auth/signup \
  -H "Content-Type: application/json" \
  -d '{"email":"you@example.com","password":"at least 8 chars"}'
# -> { "token": "...", "userId": "..." }

# use the token to ask a question
curl -X POST http://localhost:3000/api/questions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_TOKEN" \
  -d '{"text":"Should I take the new job?","category":"career"}'

# or post a confession (same auth requirement, different anonymity guarantee)
curl -X POST http://localhost:3000/api/questions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_TOKEN" \
  -d '{"text":"Something I have never told anyone.","kind":"confession"}'

# responding never needs a token - just a pseudonymous responder_id
# (the frontend creates and stores one automatically)
curl -X POST http://localhost:3000/api/users -d '{}'
```

## Files

```
src/
  auth.js                    - password hashing + session tokens
  db.js                       - schema: users, sessions, questions (incl. confessions), responses, flags, etc.
  moderation.js                - crisis + policy-violation detection (stub, see in-file comments)
  realtime.js                   - WebSocket pub/sub per question
  featureFlags.js                - feature flag read/write helpers
  server.js                       - wires it all together
  routes/
    users.js                      - pseudonymous accounts (for answering only)
    auth.js                        - signup / login
    questions.js                    - ask, read, confessions feed, 30-day paywall
    responses.js                     - threaded replies
    dataControl.js                    - retain toggle + full data deletion
    admin.js                           - moderation review queue
    featureFlagsRoute.js                - admin flag management
  jobs/
    retentionSweep.js                    - deletes expired questions/responses (respects retain flag)
    seedFlags.js                          - one-time default flag setup
public/
  index.html                              - full frontend: auth, tabs, threaded replies, confessions, full-page theming
```
