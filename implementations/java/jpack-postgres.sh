
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

# Location of the PostgtreSQL connector for Java. Visit: https://jdbc.postgresql.org/
POSTGRES_JDBC="$LIBS_DIR/postgresql-42.7.10.jar"

[ -d $TMP_DIR ] || mkdir $TMP_DIR

javac  -d $TMP_DIR -cp "$SRC_DIR:$POSTGRES_JDBC" $SRC_FILE

cd $TMP_DIR
unzip -uo $POSTGRES_JDBC > /dev/null

jar -cfe "$OUT_FILE" "$CLASS" .

cd ..
rm -rf $TMP_DIR

echo "JAR successfully generated in: $OUT_FILE"
