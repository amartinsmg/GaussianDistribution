const { gaussianCDF } = require("./gaussian"),
  sqlite3 = require("sqlite3").verbose();

try {
  let dbPath = __dirname + "/../../sqlite/database.db",
    conn = new sqlite3.Database(dbPath);
  conn.exec(
    "DROP TABLE IF EXISTS js_serial; CREATE TABLE js_serial(id INTEGER PRIMARY KEY " +
      "AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);"
  );
  for (let i = -500; i <= 500; i++) {
    let x = i / 100,
      prob = gaussianCDF(0, 1, x);
    conn.exec(
      `INSERT INTO js_serial(z_score, cumulative_distribution) VALUES (${x}, ${prob.toFixed(
        6
      )});`
    );
  }
  conn.close();
} catch (err) {
  console.log(err.message);
}
