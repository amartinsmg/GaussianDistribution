
import java.io.File;
import java.sql.*;

public class SQLiteSerial {

    public static void main(String[] args) {
        String dbPath = String.format("jdbc:sqlite:%s/database.db",
                new File(SQLiteSerial.class.getProtectionDomain().getCodeSource().getLocation().getPath())
                        .getParent());
        String query;
        int i, hash;
        try (Connection conn = DriverManager.getConnection(dbPath); Statement stmt = conn.createStatement();) {
            stmt.executeUpdate("DROP TABLE IF EXISTS tb_java_serial;"
                    + "CREATE TABLE tb_java_serial "
                    + "(id INTEGER AUTO_INCREMENT PRIMARY KEY, "
                    + "hash INTEGER NOT NULL)");

            for (i = 1; i <= 10000; i++) {
                hash = Hash.hash32(i);
                query = String.format("INSERT INTO tb_java_serial(hash) VALUES (%d)", hash);
                stmt.executeUpdate(query);
            }

        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
