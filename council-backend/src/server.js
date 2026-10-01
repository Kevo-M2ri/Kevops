const express = require("express");
const http = require("http");
const path = require("path");

const { ensureDefaults } = require("./featureFlags");
const { attachRealtime } = require("./realtime");

const usersRouter = require("./routes/users");
const authRouter = require("./routes/auth");
const questionsRouter = require("./routes/questions");
const responsesRouter = require("./routes/responses");
const adminRouter = require("./routes/admin");
const featureFlagsRouter = require("./routes/featureFlagsRoute");
const dataControlRouter = require("./routes/dataControl");

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

app.use("/api/users", usersRouter());       // anonymous pseudonymous accounts (for answering only)
app.use("/api/auth", authRouter());          // real accounts (required for questions/confessions)
app.use("/api/questions", questionsRouter());
app.use("/api/questions", responsesRouter(broadcast)); // adds /:id/responses under the same prefix
app.use("/api/admin", adminRouter());
app.use("/api/feature-flags", featureFlagsRouter());
app.use("/api", dataControlRouter());        // /api/questions/:id/retain, /api/users/me/data

app.get("/api/health", (req, res) => res.json({ ok: true }));

const PORT = process.env.PORT || 3000;
server.listen(PORT, "0.0.0.0", () => {
  console.log(`Council backend listening on 0.0.0.0:${PORT}`);
});
