# Council — backend (MVP reference implementation)

This is a working implementation of the architecture from the design docs:
questions, live crowd responses, sentiment/synthesis scoring, moderation
holds, an admin review queue, feature flags, and a retention sweeper.

It's built to run with **zero external services** (SQLite instead of
Postgres, an in-process WebSocket instead of managed pub/sub) so it's easy
to run and inspect locally. Swap the pieces called out in each file's
comments (`db.js`, `moderation.js`, `ai.js`, `realtime.js`) for production
infrastructure when you're ready — the rest of the app doesn't need to
change.

## Run it

```bash
npm install
npm run seed:flags   # creates default feature flags (only needed once)
npm start             # starts the server on http://localhost:3000
```

Open `http://localhost:3000` for the live demo page — ask a question, then
open a second browser tab to the same URL... actually, since this demo
uses one shared pseudonymous user per browser session, the simplest way to
see the full flow is to open the page, ask a question, and answer it
yourself a few times to watch the live tally and marker update, then watch
the synthesis panel appear once you cross the notification threshold.

## Test the pieces individually

**Lower the notification threshold** so you don't need 100 real responses to see the synthesis fire:
```bash
curl -X PATCH http://localhost:3000/api/feature-flags/notification_threshold \
  -H "Content-Type: application/json" \
  -d '{"enabled":1,"value":"5","updated_by":"you"}'
```

**Trigger the moderation hold** by asking a question containing a crisis-signal or spam phrase — it will come back `held_for_review` instead of `active`, and show up at:
```bash
curl http://localhost:3000/api/admin/flags
```

**Resolve a flag:**
```bash
curl -X POST http://localhost:3000/api/admin/flags/<flag_id>/decision \
  -H "Content-Type: application/json" \
  -d '{"decision":"remove","actor_id":"reviewer-1","reason":"why"}'
```

**Run the retention sweep manually:**
```bash
npm run sweep
```
In production this runs on a daily schedule (cron, a scheduled cloud
function, etc.) rather than by hand.

## What's a stub vs. what's real here

- **Real**: the data model, the request/moderation-hold/publish pipeline, the live WebSocket tally, the threshold-triggered synthesis, the feature-flag system, the retention sweeper, the audit log.
- **Stubbed, clearly marked in-file**: the moderation classifier (`moderation.js`) uses keyword matching, not a real classification model; the sentiment/constructiveness scorer (`ai.js`) uses simple heuristics, not a real language model. Both have the same function signatures a real implementation would use, so swapping them in later doesn't require touching the routes.
- **Not built here**: payment/subscription integration, real authentication, and anything client-side beyond the one demo HTML page — see the other design docs for those.

## Files

```
src/
  db.js                  - SQLite schema (maps to the data model doc)
  moderation.js           - crisis + policy-violation detection (stub)
  ai.js                    - sentiment/constructiveness scoring + synthesis (stub)
  realtime.js              - WebSocket pub/sub per question
  featureFlags.js          - feature flag read/write helpers
  server.js                - wires it all together
  routes/
    users.js               - pseudonymous account creation
    questions.js            - create/fetch questions
    responses.js             - submit responses, live broadcast, synthesis trigger
    admin.js                  - review queue + flag decisions + audit log
    featureFlagsRoute.js       - admin flag management
  jobs/
    retentionSweep.js          - deletes expired questions/responses
    seedFlags.js                 - one-time default flag setup
public/
  index.html                     - working demo frontend (REST + WebSocket)
```
