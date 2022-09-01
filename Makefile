CC=gcc
IncludeSQLite_path=-I"include"
LibSQLite_path=-L"libs"

all: c_sqlite_serial c_sqlite_block cs_sqlite_serial cs_sqlite_block java_sqlite_serial java_sqlite_block

dir:
	[ -d build ] || mkdir build

c_sqlite_serial: dir
	$(CC) -o build/c_sqlite_serial $(IncludeSQLite_path) $(LibSQLite_path) src/c/sqlite_serial.c -lsqlite3
	
c_sqlite_block: dir
	$(CC) -o build/c_sqlite_block $(IncludeSQLite_path) $(LibSQLite_path) src/c/sqlite_block.c -lsqlite3

cs_sqlite_serial: dir
	compile_cs.sh src/cs/sqlite_serial.cs

cs_sqlite_block: dir
	compile_cs.sh src/cs/sqlite_block.cs

java_sqlite_serial: dir
	compile_java.sh src/java/SQLite_serial.java

java_sqlite_block: dir
	compile_java.sh src/java/SQLite_block.java

clean:
	rm -rf build/*
