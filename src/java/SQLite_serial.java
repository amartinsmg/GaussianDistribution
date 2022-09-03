import java.io.File;
import java.sql.*;
import java.util.Locale;

public class SQLite_serial {
  public static void main(String[] args) {
    Connection conn;
    Statement stmt;
    String dbPath = String.format("jdbc:sqlite:%s/../sqlite/database.db",
        new File(SQLite_serial.class.getProtectionDomain().getCodeSource().getLocation().getPath().toString())
            .getParent());
    int i;
    double x, prob;
    Locale.setDefault(new Locale("en", "US"));
    try {
      conn = DriverManager.getConnection(dbPath);
      stmt = conn.createStatement();
      stmt.executeUpdate("DROP TABLE IF EXISTS java_serial; CREATE TABLE java_serial(id INTEGER PRIMARY KEY " +
          "AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");
      for (i = -500; i <= 500; i++) {
        x = (double) i / 100.0;
        prob = Gaussian.gaussianCDF(0, 1, x);
        stmt.executeUpdate(
            String.format("INSERT INTO java_serial(z_score, cumulative_distribution) VALUES (%.2f, %f)", x, prob));
      }
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }
}
