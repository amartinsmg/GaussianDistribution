SQLITE_JDBC=libs/sqlite-jdbc-3.51.2.0.jar

all: sqlite-serial sqlite-block mysql-serial mysql-block postgres-serial postgres-block

sqlite-serial: dir
	bash jpack-sqlite.sh SQLite_serial

sqlite-block: dir
	bash jpack-sqlite.sh SQLite_block

mysql-serial: dir
	bash jpack-mysql.sh MySQL_serial

mysql-block: dir
	bash jpack-mysql.sh MySQL_block

postgres-serial: dir
	bash jpack-postgres.sh Postgres_serial

postgres-block: dir
	bash jpack-postgres.sh Postgres_block

dir:
	mkdir -p out

clean:
	rm -rf out/*
