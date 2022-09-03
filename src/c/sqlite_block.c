#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "gaussian.h"

int main(int argc, char **argv)
{
  sqlite3 *conn;
  int exitCode, i,
      buffer = 0;
  double x, prob;
  char dbPath[300],
      *query = (char *)malloc(90000 * sizeof(*query)),
      *errMsg = NULL;
  sprintf(dbPath, "%s/../sqlite/database.db", argc ? dirname(argv[0]) : ".");
  exitCode = sqlite3_open(dbPath, &conn);
  if (exitCode)
  {
    fprintf(stderr, "Connection to database failed\n");
    exit(-1);
  }
  exitCode = sqlite3_exec(conn, "DROP TABLE IF EXISTS c_block; CREATE TABLE c_block(id INTEGER PRIMARY KEY "
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
    prob = gaussianCDF(0, 1, x);
    buffer += sprintf((char *)(query + buffer), "INSERT INTO c_block(z_score, cumulative_distribution) VALUES (%.2f, %f);", x, prob);
  }
  exitCode = sqlite3_exec(conn, query, 0, 0, &errMsg);
  if (exitCode)
  {
    fprintf(stderr, "%s\n", errMsg);
    exit(-1);
  }
  free(query);
  sqlite3_close(conn);
  return 0;
}