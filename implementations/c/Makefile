# Location of the Postgres C header files.
POSTGRES_INCLUDE=-I"/usr/include/postgresql"
# Location of the MySQL C header files.
MYSQL_INCLUDE=-I"/usr/include/mysql"


all: sqlite postgres mysql

sqlite: sqlite-serial sqlite-batch sqlite-bulk 

postgres: postgres-serial postgres-batch postgres-bulk 

mysql: mysql-serial mysql-batch mysql-bulk

sqlite-serial: dir
	gcc  src/sqlite-serial.c -o build/sqlite-serial -Iinclude -lsqlite3
	
sqlite-batch: dir
	gcc  src/sqlite-batch.c -o build/sqlite-batch -Iinclude -lsqlite3

sqlite-bulk: dir
	gcc  src/sqlite-bulk.c -o build/sqlite-bulk -Iinclude -lsqlite3

postgres-serial: dir
	gcc src/postgres-serial.c -o build/postgres-serial $(POSTGRES_INCLUDE) -Iinclude -lpq
	
postgres-batch: dir
	gcc src/postgres-batch.c -o build/postgres-batch $(POSTGRES_INCLUDE) -Iinclude -lpq

postgres-bulk: dir
	gcc src/postgres-bulk.c -o build/postgres-bulk $(POSTGRES_INCLUDE) -Iinclude -lpq

mysql-serial: dir
	gcc src/mysql-serial.c -o build/mysql-serial $(MYSQL_INCLUDE) -Iinclude -lmysqlclient
	
mysql-batch: dir
	gcc src/mysql-batch.c -o build/mysql-batch $(MYSQL_INCLUDE) -Iinclude -lmysqlclient
	
mysql-bulk: dir
	gcc src/mysql-bulk.c -o build/mysql-bulk $(MYSQL_INCLUDE) -Iinclude -lmysqlclient

dir: 
	mkdir -p build

clean:
	rm -rf build/*

