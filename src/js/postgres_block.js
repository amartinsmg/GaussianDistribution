const { gaussianCDF } = require("./gaussian"),
  { Pool } = require("pg");

void (async function () {
  let query = "",
    pool,
    conn;
  try {
    pool = new Pool({
      host: "localhost",
      database: "gaussian",
      user: "root",
      password: "root123",
    });
    conn = await pool.connect();

    conn.query(
      "DROP TABLE IF EXISTS js_block; CREATE TABLE js_block(id SERIAL " +
        "PRIMARY KEY, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);"
    );

    for (let i = -500; i <= 500; i++) {
      let x = i / 100,
        prob = gaussianCDF(0, 1, x);
      query += `INSERT INTO js_block(z_score, cumulative_distribution) VALUES (${x}, ${prob.toFixed(
        6
      )});`;
    }
    conn.query(query, () => conn.end());
  } catch (err) {
    console.log(err.message);
  }
})();
