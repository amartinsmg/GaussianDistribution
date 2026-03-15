
import java.io.File;
import java.sql.*;

public class SQLiteSerial {

    public static void main(String[] args) {
        String dbPath = String.format("jdbc:sqlite:%s/database.db",
                new File(SQLiteSerial.class.getProtectionDomain().getCodeSource().getLocation().getPath())
                        .getParent());
        int i, hash;
        try (
            Connection conn = DriverManager.getConnection(dbPath);
            Statement stmt = conn.createStatement();
            PreparedStatement ps = conn.prepareStatement(
                "INSERT INTO tb_java_serial(hash) VALUES (?)"
            );
		) {
			stmt.executeUpdate("DROP TABLE IF EXISTS tb_java_serial;"
					+ "CREATE TABLE tb_java_serial "
                    + "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
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
