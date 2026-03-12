SQLITE_JDBC=libs/sqlite-jdbc-3.51.2.0.jar

all: sqlite-serial sqlite-block sqlite-bulk mysql-serial mysql-block mysql-bulk postgres-serial postgres-block postgres-bulk

sqlite-serial: dir
	bash jpack-sqlite.sh SQLiteSerial

sqlite-block: dir
	bash jpack-sqlite.sh SQLiteBlock

sqlite-bulk: dir
	bash jpack-sqlite.sh SQLiteBulk

mysql-serial: dir
	bash jpack-mysql.sh MySQLSerial

mysql-block: dir
	bash jpack-mysql.sh MySQLBlock

mysql-bulk: dir
	bash jpack-mysql.sh MySQLBulk

postgres-serial: dir
	bash jpack-postgres.sh PostgresSerial

postgres-block: dir
	bash jpack-postgres.sh PostgresBlock

postgres-bulk: dir
	bash jpack-postgres.sh PostgresBulk

dir:
	mkdir -p out

clean:
	rm -rf out/*
