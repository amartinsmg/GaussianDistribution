import java.sql.*;
import java.util.Locale;

public class MySQL_serial {
  public static void main(String[] args) {
    Connection conn;
    Statement stmt;
    String query = "";
    int i;
    double x, prob;
    Locale.setDefault(new Locale("en", "US"));
    try {
      conn = DriverManager.getConnection("jdbc:mysql://localhost/gaussian?allowMultiQueries=true", "root", "root123");
      stmt = conn.createStatement();
      stmt.executeUpdate("DROP TABLE IF EXISTS java_serial; CREATE TABLE java_serial(id INTEGER AUTO_INCREMENT " +
      "PRIMARY KEY, z_score FLOAT NOT NULL, cumulative_distribution FLOAT NOT NULL)");
      for (i = -500; i <= 500; i++) {
        x = (double) i / 100.0;
        prob = Gaussian.gaussianCDF(0, 1, x);
        query = String.format("INSERT INTO java_serial(z_score, cumulative_distribution) VALUES (%.2f, %f);", x, prob);
        stmt.executeUpdate(query);
      }
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }
}
