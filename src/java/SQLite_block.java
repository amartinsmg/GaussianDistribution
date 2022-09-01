import java.io.File;
import java.sql.*;
import java.util.Locale;

public class SQLite_block {
  public static void main(String[] args) {
    String query = "",
    databasePath = "jdbc:sqlite:" + new File(
        SQLite_serial.class.getProtectionDomain().getCodeSource().getLocation().getPath().toString()).getParent()
        + "\\..\\sqlite\\database.db";
    int i;
    double x, cumulativeD;
    Locale.setDefault(new Locale("en", "US"));
    try {
      Connection db = DriverManager.getConnection(databasePath);
      Statement stmt = db.createStatement();
      stmt.executeUpdate("DROP TABLE IF EXISTS java_block; CREATE TABLE java_block(id INTEGER PRIMARY KEY " +
          "AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");
      for (i = -500; i <= 500; i++) {
        x = (double)i / 100.0;
        cumulativeD = Gaussian.gaussianCDF(0, 1, x);
        query += String.format("INSERT INTO java_block(z_score, cumulative_distribution) VALUES (%.2f, %f);", x, cumulativeD);
      }
      stmt.executeUpdate(query);
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }
}
