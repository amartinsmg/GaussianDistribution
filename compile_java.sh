#!/bin/bash


JAVAFILE=$(echo $1 | sed 's/src\/java\///g')
CLASS=$(echo $JAVAFILE | sed 's/\.java//g')
OUTPUT="$(echo $CLASS | tr '[:upper:]' '[:lower:]').jar"
SQLITE_JDBC="libs/sqlite-jdbc-3.36.0.3.jar"

mkdir build/tmp

if [ ! -f "$SQLITE_JDBC" ]
then
  [ -d libs ] || mkdir libs
  cd libs
  curl -LO https://github.com/xerial/sqlite-jdbc/releases/download/3.36.0.3/sqlite-jdbc-3.36.0.3.jar
  cd ..
fi

cd src/java
javac $JAVAFILE
mv *.class ../../build/tmp
cd ../../build/tmp
unzip -uo "../../$SQLITE_JDBC"
cd ..
jar -cfe $OUTPUT $CLASS -C tmp .
rm -rf tmp


