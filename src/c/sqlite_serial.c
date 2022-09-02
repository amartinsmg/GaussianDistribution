#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "gaussian.h"

int main(int argc, char **argv)
{
  sqlite3 *conn;
  int exitCode, i;
  double x, cumulativeD;
  char databasePath[300],
      query[300],
      *errMsg = NULL;
  sprintf(databasePath, "%s/../sqlite/database.db", argc ? dirname(argv[0]) : ".");
  exitCode = sqlite3_open(databasePath, &conn);
  if (exitCode)
  {
    fprintf(stderr, "Connection to database failed\n");
    exit(-1);
  }
  exitCode = sqlite3_exec(conn, "DROP TABLE IF EXISTS c_serial; CREATE TABLE c_serial(id INTEGER PRIMARY KEY "
                              "AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)",
                          0, 0, &errMsg);
  if (exitCode)
  {
    fprintf(stderr, "%s\n", errMsg);
    exit(-1);
  }
  for (i = -500; i <= 500; i++)
  {
    x = (double)i / 100.0;
    cumulativeD = gaussianCDF(0, 1, x);
    sprintf(query, "INSERT INTO c_serial(z_score, cumulative_distribution) VALUES (%.2f, %f)", x, cumulativeD);
    exitCode = sqlite3_exec(conn, query, 0, 0, &errMsg);
    if (exitCode)
    {
      fprintf(stderr, "%s\n", errMsg);
      exit(-1);
    }
  }
  sqlite3_close(conn);
  return 0;
}