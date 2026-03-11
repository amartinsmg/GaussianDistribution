SQLITE_JDBC=libs/sqlite-jdbc-3.51.2.0.jar

all: sqlite-serial sqlite-block mysql-serial mysql-block postgres-serial postgres-block

sqlite-serial: dir
	bash jpack-sqlite.sh SQLiteSerial

sqlite-block: dir
	bash jpack-sqlite.sh SQLiteBlock

mysql-serial: dir
	bash jpack-mysql.sh MySQLSerial

mysql-block: dir
	bash jpack-mysql.sh MySQLBlock

postgres-serial: dir
	bash jpack-postgres.sh PostgresSerial

postgres-block: dir
	bash jpack-postgres.sh PostgresBlock

dir:
	mkdir -p out

clean:
	rm -rf out/*
