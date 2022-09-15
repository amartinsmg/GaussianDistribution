import java.io.File;
import java.sql.*;
import java.util.Locale;

public class SQLite_block {
  public static void main(String[] args) {
    Connection conn;
    Statement stmt;
    String query = "",
        dbPath = String.format("jdbc:sqlite:%s/../sqlite/database.db",
            new File(SQLite_serial.class.getProtectionDomain().getCodeSource().getLocation().getPath().toString())
                .getParent());
    int i;
    double x, prob;
    Locale.setDefault(new Locale("en", "US"));
    try {
      conn = DriverManager.getConnection(dbPath);
      stmt = conn.createStatement();
      stmt.executeUpdate("DROP TABLE IF EXISTS tb_java_block; CREATE TABLE tb_java_block(id INTEGER PRIMARY KEY " +
          "AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");
      for (i = -500; i <= 500; i++) {
        x = (double) i / 100.0;
        prob = Gaussian.gaussianCDF(0, 1, x);
        query += String.format("INSERT INTO tb_java_block(z_score, cumulative_distribution) VALUES (%.2f, %f);", x, prob);
      }
      stmt.executeUpdate(query);
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }
}
