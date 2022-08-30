CC=gcc
IncludeSQLite_path=-I"include"
LibSQLite_path=-L"libs"

all: c_sqlite_serial c_sqlite_block

dir:
	[ -d build ] || mkdir build

c_sqlite_serial: dir
	$(CC) -o build/c_sqlite_serial $(IncludeSQLite_path) $(LibSQLite_path) src/c/sqlite_serial.c -lsqlite3
	
c_sqlite_block: dir
	$(CC) -o build/c_sqlite_block $(IncludeSQLite_path) $(LibSQLite_path) src/c/sqlite_block.c -lsqlite3
	
clean:
	rm -rf build/*
