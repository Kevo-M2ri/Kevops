const express = require("express");
const { listFlags, setFlag } = require("../featureFlags");

function featureFlagsRouter() {
  const router = express.Router();

  router.get("/", (req, res) => {
    res.json({ flags: listFlags() });
  });

  router.patch("/:key", (req, res) => {
    const { enabled, value, updated_by } = req.body || {};
    const updated = setFlag(req.params.key, { enabled, value, updated_by });
    res.json({ flag: updated });
  });

  return router;
}

module.exports = featureFlagsRouter;
