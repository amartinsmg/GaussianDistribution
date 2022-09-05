CC=gcc
IncludeSQLite_path=-I"include"
LibSQLite_path=-L"libs"
IncludePostgres_path=-I"C:/Program Files/PostgreSQL/14/include"
LibPostgres_path=-L"C:/Program Files/PostgreSQL/14/lib"
IncludeMySQL_path=-I"C:/Program Files/MySQL/MySQL Server 8.0/include"
LibMySQL_path=-L"C:/Program Files/MySQL/MySQL Server 8.0/lib"
LibMySQL_dll="C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.dll"

all: c cs java

c: c_sqlite_serial c_sqlite_block c_mysql_serial c_mysql_block c_postgres_serial c_postgres_block

cs: cs_sqlite_serial cs_sqlite_block cs_mysql_serial cs_mysql_block

java: java_sqlite_serial java_sqlite_block java_mysql_serial java_mysql_block

dir:
	[ -d build ] || mkdir build

c_sqlite_serial: dir
	$(CC) -o build/c_sqlite_serial $(IncludeSQLite_path) $(LibSQLite_path) src/c/sqlite_serial.c -lsqlite3
	
c_sqlite_block: dir
	$(CC) -o build/c_sqlite_block $(IncludeSQLite_path) $(LibSQLite_path) src/c/sqlite_block.c -lsqlite3

c_postgres_serial: dir
	$(CC) -o build/c_postgres_serial $(IncludePostgres_path) $(LibPostgres_path) src/c/postgres_serial.c -lpq
	
c_postgres_block: dir
	$(CC) -o build/c_postgres_block $(IncludePostgres_path) $(LibPostgres_path) src/c/postgres_block.c -lpq

c_mysql_serial: dir mysql_dll
	$(CC) -o build/c_mysql_serial $(IncludeMySQL_path) $(LibMySQL_path) src/c/mysql_serial.c -lmysql
	
c_mysql_block: dir mysql_dll
	$(CC) -o build/c_mysql_block $(IncludeMySQL_path) $(LibMySQL_path) src/c/mysql_block.c -lmysql

cs_sqlite_serial: dir
	compile_cs.sh src/cs/sqlite_serial.cs

cs_sqlite_block: dir
	compile_cs.sh src/cs/sqlite_block.cs

cs_mysql_serial: dir
	compile_cs.sh src/cs/mysql_serial.cs

cs_mysql_block: dir
	compile_cs.sh src/cs/mysql_block.cs

java_sqlite_serial: dir
	compile_java.sh --sqlite src/java/SQLite_serial.java

java_sqlite_block: dir
	compile_java.sh --sqlite src/java/SQLite_block.java

java_mysql_serial: dir
	compile_java.sh --mysql src/java/MySQL_serial.java

java_mysql_block: dir
	compile_java.sh --mysql src/java/MySQL_block.java

mysql_dll:
	cp $(LibMySQL_dll) build

clean:
	rm -rf build/*
