const { ensureDefaults, listFlags } = require("../featureFlags");

ensureDefaults();
console.log("Feature flags ready:");
console.table(listFlags());
