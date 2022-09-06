const { gaussianCDF } = require("./gaussian"),
  mysql = require("mysql2"),
  callback = function (err) {
    if (err) console.log(err.message);
  };

let conn = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "root123",
    database: "gaussian",
    flags: "MULTI_STATEMENTS",
  });

conn.connect(callback);

conn.query(
  "DROP TABLE IF EXISTS js_serial; CREATE TABLE js_serial(id INTEGER AUTO_INCREMENT " +
    "PRIMARY KEY, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);",
  callback
);

for (let i = -500; i <= 500; i++) {
  let x = i / 100,
    prob = gaussianCDF(0, 1, x);
  conn.query(
    `INSERT INTO js_serial(z_score, cumulative_distribution) VALUES (${x}, ${prob.toFixed(
      6
    )});`,
    callback
  );
}

conn.end();

