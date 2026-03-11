
import java.sql.*;

public class Postgres_serial {

    public static void main(String[] args) {
        String query;
        int i, hash;
        try (
            Connection conn = DriverManager.getConnection("jdbc:postgresql://127.0.0.1:5432/hashes", "root", "root123");
            Statement stmt = conn.createStatement();
        ) {
            stmt.executeUpdate("DROP TABLE IF EXISTS tb_java_serial; CREATE TABLE tb_java_serial(id SERIAL "
                    + "PRIMARY KEY, hash INTEGER NOT NULL)");
            for (i = 0; i <= 1000; i++) {
                hash = Hash.hash32(i);
                query = String.format("INSERT INTO tb_java_serial(hash) VALUES (%d)", hash);
                stmt.executeUpdate(query);
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
