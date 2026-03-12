SQLITE_JDBC=libs/sqlite-jdbc-3.51.2.0.jar

all: sqlite-serial sqlite-block sqlite-bulk mysql-serial mysql-block mysql-bulk postgres-serial postgres-block postgres-bulk

sqlite-serial: dir
	bash jpack-sqlite.sh SQLiteSerial

sqlite-block: dir
	bash jpack-sqlite.sh SQLiteBatch

sqlite-bulk: dir
	bash jpack-sqlite.sh SQLiteBulk

mysql-serial: dir
	bash jpack-mysql.sh MySQLSerial

mysql-block: dir
	bash jpack-mysql.sh MySQLBatch

mysql-bulk: dir
	bash jpack-mysql.sh MySQLBulk

postgres-serial: dir
	bash jpack-postgres.sh PostgresSerial

postgres-block: dir
	bash jpack-postgres.sh PostgresBatch

postgres-bulk: dir
	bash jpack-postgres.sh PostgresBulk

dir:
	mkdir -p out

clean:
	rm -rf out/*
