
import java.sql.*;

public class PostgresBlock {

    public static void main(String[] args) {
        StringBuilder sb = new StringBuilder();
        String query;
        int i, hash;
        try (
            Connection conn = DriverManager.getConnection(
                    "jdbc:postgresql://127.0.0.1:5432/hashes",
                    "root",
                    "root123"
            );
            Statement stmt = conn.createStatement();
        ){
            stmt.executeUpdate("DROP TABLE IF EXISTS tb_java_block;"
                    + "CREATE TABLE tb_java_block"
                    + "(id SERIAL PRIMARY KEY,"
                    + " hash INTEGER NOT NULL)");

            conn.setAutoCommit(false);

            for (i = 1; i <= 10000; i++) {
                hash = Hash.hash32(i);
                sb.append(String.format("INSERT INTO tb_java_block(hash) VALUES (%d);", hash));
            }

            query = sb.toString();

            stmt.execute(query);

            conn.commit();

        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
