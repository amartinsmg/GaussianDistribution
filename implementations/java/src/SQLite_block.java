
import java.io.File;
import java.sql.*;

public class SQLite_block {

    public static void main(String[] args) {
        String dbPath = String.format("jdbc:sqlite:%s/database.db",
                new File(SQLite_block.class.getProtectionDomain().getCodeSource().getLocation().getPath())
                        .getParent());
        String query = "INSERT INTO tb_java_block(hash) VALUES ";
        int i, hash;
        try (Connection conn = DriverManager.getConnection(dbPath); Statement stmt = conn.createStatement();) {
            stmt.executeUpdate("DROP TABLE IF EXISTS tb_java_block; CREATE TABLE tb_java_block(id INTEGER PRIMARY KEY "
                    + "AUTOINCREMENT, hash INTEGER NOT NULL)");
            for (i = 0; i <= 1000; i++) {
                hash = Hash.hash32(i);
                query += String.format("(%d),", hash);
            }
            query = query.replaceAll(".$", ";");
            stmt.executeUpdate(query);
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
