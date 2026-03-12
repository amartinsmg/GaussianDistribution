
import java.sql.*;

public class MySQLBulk {

    public static void main(String[] args) {
        StringBuilder sb = new StringBuilder("INSERT INTO tb_java_bulk(hash) VALUES ");
        String query;
        int i, hash;
        try (
            Connection conn = DriverManager.getConnection(
                    "jdbc:mysql://127.0.0.1:3306/hashes?allowMultiQueries=true",
                    "root",
                    "root123"
            );
            Statement stmt = conn.createStatement();    
        ) {
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
