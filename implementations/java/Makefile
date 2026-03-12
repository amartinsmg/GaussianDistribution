SQLITE_JDBC=libs/sqlite-jdbc-3.51.2.0.jar

all: sqlite mysql postgres

sqlite: sqlite-serial sqlite-batch sqlite-bulk 

mysql: mysql-serial mysql-batch mysql-bulk

postgres: postgres-serial postgres-batch postgres-bulk 

sqlite-serial: dir
	bash jpack-sqlite.sh SQLiteSerial

sqlite-batch: dir
	bash jpack-sqlite.sh SQLiteBatch

sqlite-bulk: dir
	bash jpack-sqlite.sh SQLiteBulk

mysql-serial: dir
	bash jpack-mysql.sh MySQLSerial

mysql-batch: dir
	bash jpack-mysql.sh MySQLBatch

mysql-bulk: dir
	bash jpack-mysql.sh MySQLBulk

postgres-serial: dir
	bash jpack-postgres.sh PostgresSerial

postgres-batch: dir
	bash jpack-postgres.sh PostgresBatch

postgres-bulk: dir
	bash jpack-postgres.sh PostgresBulk

dir:
	mkdir -p out

clean:
	rm -rf out/*
