#!/bin/bash

OUTPUT=$(echo $1 | sed 's/src\/cs\//build\/cs_/g;s/\.cs/\.exe/g')

if [ ! -d dotnetProj ]
then
  mkdir dotnetProj
  cd dotnetProj
  dotnet new console
  dotnet add package System.Data.Sqlite
  cp ../src/cs/gaussian.cs ./
  cd ..
fi

cd dotnetProj
cp "../$1" ./Program.cs

dotnet publish -r win-x64 -p:PublishSingleFile=true -p:IncludeNativeLibrariesForSelfExtract=true \
-p:DebugType=None -p:DebugSymbols=false --self-contained true -o ../build

cd ..

mv build/dotnetProj.exe $OUTPUT
