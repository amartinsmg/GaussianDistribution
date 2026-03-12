
import java.io.File;
import java.sql.*;

public class SQLiteBatch {

    public static void main(String[] args) {
        String dbPath = String.format("jdbc:sqlite:%s/database.db",
                new File(SQLiteBatch.class.getProtectionDomain().getCodeSource().getLocation().getPath())
                        .getParent());
        StringBuilder sb = new StringBuilder();
        String query;
        int i, hash;
        try (Connection conn = DriverManager.getConnection(dbPath); Statement stmt = conn.createStatement();) {
            stmt.executeUpdate("DROP TABLE IF EXISTS tb_java_batch;"
                    + "CREATE TABLE tb_java_batch"
                    + "(id INTEGER AUTO_INCREMENT PRIMARY KEY,"
                    + " hash INTEGER NOT NULL)");

            conn.setAutoCommit(false);

            for (i = 1; i <= 10000; i++) {
                hash = Hash.hash32(i);
                sb.append(String.format("INSERT INTO tb_java_batch(hash) VALUES (%d);", hash));
            }

            query = sb.toString();

            stmt.execute(query);

            conn.commit();

        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
