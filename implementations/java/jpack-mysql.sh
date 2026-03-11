#!/bin/ bash

if [ -z "$1" ]; then
    echo "Use: $0 ClassName"
    exit 1
fi

CLASS=$1
SRC_DIR="`pwd`/src"
LIBS_DIR="`pwd`/libs"
TMP_DIR="`pwd`/tmp"
OUT_DIR="`pwd`/out"
SRC_FILE="$SRC_DIR/$CLASS.java"
OUT_FILE="$OUT_DIR/$CLASS.jar"

# Location of the MySQL connector for Java. Visit: https://dev.mysql.com/downloads/connector/j/
MYSQL_JDBC="$LIBS_DIR/mysql-connector-j-9.6.0.jar"

[ -d $TMP_DIR ] || mkdir $TMP_DIR

javac  -d $TMP_DIR -cp "$SRC_DIR:$MYSQL_JDBC" $SRC_FILE

cd $TMP_DIR
unzip -uo $MYSQL_JDBC > /dev/null

jar -cfe "$OUT_FILE" "$CLASS" .

cd ..
rm -rf $TMP_DIR

echo "JAR successfully generated in: $OUT_FILE"
