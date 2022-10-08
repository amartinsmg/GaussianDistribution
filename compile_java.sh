#!/bin/bash

SRC_DIR="`pwd`/src/java"
LIBS_DIR="`pwd`/libs"
BUILD_DIR="`pwd`/build"
TMP_DIR="$BUILD_DIR/tmp"
JAVAFILE=$(echo $2 | sed 's/src\/java\///g')
CLASS=$(echo $JAVAFILE | sed 's/\.java//g')
OUTPUT="$(echo $CLASS | tr '[:upper:]' '[:lower:]').jar"
# Location of the SQLite connector for Java. Visit: https://mvnrepository.com/artifact/org.xerial/sqlite-jdbc
SQLITE_JDBC="$LIBS_DIR/sqlite-jdbc-3.36.0.3.jar"
# Location of the PostgtreSQL connector for Java. Visit: https://jdbc.postgresql.org/
POSTGRES_JDBC="$LIBS_DIR/postgresql-42.5.0.jar"
# Location of the MySQL connector for Java. Visit: https://dev.mysql.com/downloads/connector/j/
MYSQL_JDBC="C:/Program Files (x86)/MySQL/Connector J 8.0/mysql-connector-java-8.0.30.jar"

mkdir "$TMP_DIR"
cd "$SRC_DIR"
javac $JAVAFILE
mv *.class "$TMP_DIR"

case $1 in
  "--sqlite")
    if [ ! -f "$SQLITE_JDBC" ]
    then
      [ -d "$LIBS_DIR" ] || mkdir "$LIBS_DIR"
      cd "$LIBS_DIR"
      curl -LO https://github.com/xerial/sqlite-jdbc/releases/download/3.36.0.3/sqlite-jdbc-3.36.0.3.jar
    fi
    cd "$TMP_DIR"
    unzip -uo $SQLITE_JDBC
    cd "$BUILD_DIR"
    jar -cfe "$OUTPUT" $CLASS -C "$TMP_DIR" .
    rm -rf "$TMP_DIR"
  ;;

  "--mysql")
    cd "$TMP_DIR"
    unzip -uo "$MYSQL_JDBC"
    cd "$BUILD_DIR"
    jar -cfe "$OUTPUT" $CLASS -C "$TMP_DIR" .
    rm -rf "$TMP_DIR"
  ;;

  "--postgres")
    if [ ! -f "$POSTGRES_JDBC" ]
    then
      [ -d "$LIBS_DIR" ] || mkdir "$LIBS_DIR"
      cd "$LIBS_DIR"
      curl -LO https://jdbc.postgresql.org/download/postgresql-42.5.0.jar
    fi
    cd "$TMP_DIR"
    unzip -uo "$POSTGRES_JDBC"
    cd "$BUILD_DIR"
    jar -cfe "$OUTPUT" $CLASS -C "$TMP_DIR" .
    rm -rf "$TMP_DIR"
  ;;
esac

