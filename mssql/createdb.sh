#!/bin/bash

for i in {1..50}; do
  /opt/mssql-tools/bin/sqlcmd -S localhost -U sa -P root123% -d master -i createdb.sql
  [ $? == 0 ] && echo "gaussian database created successufully" && break
  sleep 1
done
