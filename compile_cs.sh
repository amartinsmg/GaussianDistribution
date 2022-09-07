#!/bin/bash

SRC_FILE="`pwd`/$1"
GAUSSIAN_SRC_FILE="`pwd`/src/cs/gaussian.cs"
BUILD_DIR="`pwd`/build"
OUTPUT="$BUILD_DIR/$(echo $1 | sed 's/src\/cs\//\/cs_/g;s/\.cs/\.exe/g')"
DOTNETPROJ_DIR="`pwd`/dotnetProj"

if [ ! -d $DOTNETPROJ_DIR ]
then
  mkdir $DOTNETPROJ_DIR
  cd $DOTNETPROJ_DIR
  dotnet new console
  dotnet add package System.Data.Sqlite
  dotnet add package MySqlConnector
  dotnet add package Npgsql
  cp $GAUSSIAN_SRC_FILE ./
else
  cd $DOTNETPROJ_DIR
fi

cp $SRC_FILE ./Program.cs

dotnet publish -r win-x64 -p:PublishSingleFile=true -p:IncludeNativeLibrariesForSelfExtract=true \
-p:DebugType=None -p:DebugSymbols=false --self-contained true -o $BUILD_DIR

mv "$BUILD_DIR/dotnetProj.exe" $OUTPUT
