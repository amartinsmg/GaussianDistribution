
import java.io.File;
import java.sql.*;

public class SQLiteBulk {

    public static void main(String[] args) {
        String dbPath = String.format("jdbc:sqlite:%s/database.db",
                new File(SQLiteBulk.class.getProtectionDomain().getCodeSource().getLocation().getPath())
                        .getParent()
        );
        StringBuilder sb = new StringBuilder("INSERT INTO tb_java_bulk(hash) VALUES ");
        String query;
        int i, hash;
        try (Connection conn = DriverManager.getConnection(dbPath); Statement stmt = conn.createStatement();) {
            stmt.executeUpdate("DROP TABLE IF EXISTS tb_java_bulk;"
                    + "CREATE TABLE tb_java_bulk"
                    + "(id INTEGER AUTO_INCREMENT PRIMARY KEY,"
                    + " hash INTEGER NOT NULL)");

            conn.setAutoCommit(false);

            for (i = 1; i <= 10000; i++) {
                hash = Hash.hash32(i);
                sb.append(String.format("(%d),", hash));
            }

            query = sb.toString().replaceAll(".$", ";");

            stmt.execute(query);

            conn.commit();

        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
