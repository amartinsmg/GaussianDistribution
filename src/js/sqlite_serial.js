const { gaussianCDF } = require("./gaussian"),
  path = require("path"),
  sqlite3 = require("sqlite3").verbose(),
  callback = function (err) {
    if (err) console.log(err.message);
  };

let databasePath = path.resolve(__dirname, "../../sqlite/database.db"),
  db = new sqlite3.Database(databasePath, callback);

db.exec(
  "DROP TABLE IF EXISTS js_serial; CREATE TABLE js_serial(id INTEGER PRIMARY KEY " +
    "AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);",
  callback
);

for (let i = -500; i <= 500; i++) {
  let x = i / 100,
    cumulativeD = gaussianCDF(0, 1, x);
  db.exec(
    `INSERT INTO js_serial(z_score, cumulative_distribution) VALUES (${x}, ${cumulativeD.toFixed(
      6
    )});`,
    callback
  );
}

db.close();
