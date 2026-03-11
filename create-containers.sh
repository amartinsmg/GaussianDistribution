#!/bin/bash

POSTGRES_DIR="`pwd`/postgres"
MYSQL_DIR="`pwd`/mysql"
MARIADB_DIR="`pwd`/mariadb"

cd "$POSTGRES_DIR"
docker compose create

cd "$MYSQL_DIR"
docker compose create

cd "$MARIADB_DIR"
docker compose create
