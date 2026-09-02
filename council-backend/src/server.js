const express = require("express");
const http = require("http");
const path = require("path");

const { ensureDefaults } = require("./featureFlags");
const { attachRealtime } = require("./realtime");

const usersRouter = require("./routes/users");
const questionsRouter = require("./routes/questions");
const responsesRouter = require("./routes/responses");
const adminRouter = require("./routes/admin");
const featureFlagsRouter = require("./routes/featureFlagsRoute");

// Surface any crash with a real stack trace in the platform's logs, instead
// of the process just dying and the host silently restarting it (which is
// what a "stuck cold-start loop" on Render/Railway usually means - the app
// crashed right after boot and the log scrolled past the reason).
process.on("uncaughtException", (err) => {
  console.error("FATAL - uncaught exception:", err);
  process.exit(1);
});
process.on("unhandledRejection", (err) => {
  console.error("FATAL - unhandled rejection:", err);
  process.exit(1);
});

ensureDefaults();

const app = express();
app.use(express.json());
app.use(express.static(path.join(__dirname, "..", "public")));

const server = http.createServer(app);
const { broadcast } = attachRealtime(server);

app.use("/api/users", usersRouter());
app.use("/api/questions", questionsRouter());
app.use("/api/questions", responsesRouter(broadcast)); // adds /:id/responses under the same prefix
app.use("/api/admin", adminRouter());
app.use("/api/feature-flags", featureFlagsRouter());

app.get("/api/health", (req, res) => res.json({ ok: true }));

const PORT = process.env.PORT || 3000;
// Explicitly bind to 0.0.0.0 - on some cloud hosts (Render, Railway, etc.)
// Node's default binding can fail the platform's health check even though
// the app itself started fine, which looks identical to a crash loop from
// the outside.
server.listen(PORT, "0.0.0.0", () => {
  console.log(`Council backend listening on 0.0.0.0:${PORT}`);
});
