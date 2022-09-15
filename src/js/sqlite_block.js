const { gaussianCDF } = require("./gaussian"),
  sqlite3 = require("sqlite3").verbose();

try {
  let query = "",
    dbPath = __dirname + "/../../sqlite/database.db",
    conn = new sqlite3.Database(dbPath);
  conn.exec(
    "DROP TABLE IF EXISTS tb_js_block; CREATE TABLE tb_js_block(id INTEGER PRIMARY KEY " +
      "AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);"
  );
  for (let i = -500; i <= 500; i++) {
    let x = i / 100,
      prob = gaussianCDF(0, 1, x);
    query += `INSERT INTO tb_js_block(z_score, cumulative_distribution) VALUES (${x}, ${prob.toFixed(
      6
    )});`;
  }
  conn.exec(query);
  conn.close();
} catch (err) {
  console.log(err.message);
}
