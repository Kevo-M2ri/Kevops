// realtime.js
//
// Minimal pub/sub over WebSocket, scoped per question_id, matching the
// "realtime path" section of the backend architecture doc. In production
// this would sit behind Redis pub/sub (or a managed service) so it scales
// across multiple server processes; for a single-process MVP a plain
// in-memory map is enough and behaves identically from the client's side.

const { WebSocketServer } = require("ws");

function attachRealtime(server) {
  const wss = new WebSocketServer({ server });
  /** @type {Map<string, Set<import('ws').WebSocket>>} */
  const rooms = new Map();

  wss.on("connection", (ws) => {
    let subscribedQuestionId = null;

    ws.on("message", (raw) => {
      let msg;
      try {
        msg = JSON.parse(raw.toString());
      } catch {
        return;
      }
      if (msg.type === "subscribe" && msg.questionId) {
        subscribedQuestionId = msg.questionId;
        if (!rooms.has(msg.questionId)) rooms.set(msg.questionId, new Set());
        rooms.get(msg.questionId).add(ws);
      }
    });

    ws.on("close", () => {
      if (subscribedQuestionId && rooms.has(subscribedQuestionId)) {
        rooms.get(subscribedQuestionId).delete(ws);
      }
    });
  });

  function broadcast(questionId, payload) {
    const clients = rooms.get(questionId);
    if (!clients) return;
    const message = JSON.stringify(payload);
    for (const client of clients) {
      if (client.readyState === client.OPEN) client.send(message);
    }
  }

  return { broadcast };
}

module.exports = { attachRealtime };
