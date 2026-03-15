
import java.sql.*;

public class MySQLSerial {

    public static void main(String[] args) {
        int i, hash;
        try (
            Connection conn = DriverManager.getConnection(
                    "jdbc:mysql://127.0.0.1:3306/hashes?allowMultiQueries=true",
                    "root",
                    "root123"
            );
            Statement stmt = conn.createStatement();
            PreparedStatement ps = conn.prepareStatement(
                "INSERT INTO tb_java_serial(hash) VALUES (?)"
            );
		) {
			stmt.executeUpdate("DROP TABLE IF EXISTS tb_java_serial;"
					+ "CREATE TABLE tb_java_serial "
					+ "(id INTEGER AUTO_INCREMENT PRIMARY KEY, "
					+ "hash INTEGER NOT NULL)");

			for (i = 1; i <= 10000; i++) {
				hash = Hash.hash32(i);
				ps.setInt(1, hash);
                ps.executeUpdate();
			}
		} catch (Exception e) {
			System.err.println(e.getMessage());
		}
    }
}
