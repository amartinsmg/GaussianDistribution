const { gaussianCDF } = require("./gaussian"),
  sqlite3 = require("sqlite3").verbose(),
  callback = function (err) {
    if (err) console.log(err.message);
  };

let query = "",
  databasePath = __dirname + "/../../sqlite/database.db",
  conn = new sqlite3.Database(databasePath, callback);

conn.exec(
  "DROP TABLE IF EXISTS js_block; CREATE TABLE js_block(id INTEGER PRIMARY KEY " +
    "AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);",
  callback
);

for (let i = -500; i <= 500; i++) {
  let x = i / 100,
    cumulativeD = gaussianCDF(0, 1, x);
  query += `INSERT INTO js_block(z_score, cumulative_distribution) VALUES (${x}, ${cumulativeD.toFixed(
    6
  )});`;
}

conn.exec(query, callback);

conn.close();
