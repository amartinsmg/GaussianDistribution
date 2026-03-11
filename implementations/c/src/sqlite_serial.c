#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "gaussian.h"

int main(int argc, char **argv)
{
  sqlite3 *conn = NULL;
  int exitCode = -1, i;
  double x, prob;
  char dbPath[300],
      query[90],
      *errMsg = NULL;
  sprintf(dbPath, "%s/../sqlite/database.db", argc ? dirname(argv[0]) : ".");
  exitCode = sqlite3_open(dbPath, &conn);
  if (exitCode)
  {
    fprintf(stderr, "Connection to database failed\n");
    goto cleanup;
  }
  exitCode = sqlite3_exec(conn, "DROP TABLE IF EXISTS tb_c_serial; CREATE TABLE tb_c_serial(id INTEGER PRIMARY KEY "
                              "AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)",
                          0, 0, &errMsg);
  if (exitCode)
  {
    fprintf(stderr, "%s\n", errMsg);
    goto cleanup;
  }
  sqlite3_free(errMsg);
  errMsg = NULL;
  for (i = -500; i <= 500; i++)
  {
    x = (double)i / 100.0;
    prob = gaussianCDF(0, 1, x);
    sprintf(query, "INSERT INTO tb_c_serial(z_score, cumulative_distribution) VALUES (%.2f, %f)", x, prob);
    exitCode = sqlite3_exec(conn, query, 0, 0, &errMsg);
    if (exitCode)
    {
      fprintf(stderr, "%s\n", errMsg);
      goto cleanup;
    }
    sqlite3_free(errMsg);
    errMsg = NULL;
  }
  exitCode = 0;

cleanup:
  sqlite3_free(errMsg);
  if (conn != NULL)
    sqlite3_close(conn);
  return exitCode;
}
