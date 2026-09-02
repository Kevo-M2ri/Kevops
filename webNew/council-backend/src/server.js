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
server.listen(PORT, () => {
  console.log(`Council backend listening on http://localhost:${PORT}`);
});
