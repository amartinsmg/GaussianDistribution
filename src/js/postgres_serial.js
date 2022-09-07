const { gaussianCDF } = require("./gaussian"),
  pg = require("pg");

async function main() {
  let pool, conn;
  try {
    pool = new pg.Pool({
      host: "localhost",
      database: "gaussian",
      user: "root",
      password: "root123",
    });
    conn = await pool.connect();
    conn.query(
      "DROP TABLE IF EXISTS js_serial; CREATE TABLE js_serial(id SERIAL " +
        "PRIMARY KEY, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);"
    );
    for (let i = -500; i <= 500; i++) {
      let x = i / 100,
        prob = gaussianCDF(0, 1, x);
      conn.query(
        `INSERT INTO js_serial(z_score, cumulative_distribution) VALUES (${x}, ${prob.toFixed(
          6
        )});`
      );
    }
    conn.query("SELECT version", () => conn.end());
  } catch (err) {
    console.log(err.message);
  }
}

main();
