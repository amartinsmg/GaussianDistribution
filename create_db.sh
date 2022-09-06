#!/bin/bash

SQLITE_DIR="`pwd`/sqlite"
POSTGRES_DIR="`pwd`/postgres"
MYSQL_DIR="`pwd`/mysql"
MARIADB_DIR="`pwd`/mariadb"
MSSQL_DIR="`pwd`/mssql"

[ -d $SQLITE_DIR ] || mkdir $SQLITE_DIR
cd $SQLITE_DIR
sqlite3 database.db .databases

cd $POSTGRES_DIR
docker compose create

cd $MSSQL_DIR
docker compose create

cd $MARIADB_DIR
docker compose create

cd $MSSQL_DIR
docker compose create
