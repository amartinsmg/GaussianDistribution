#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <stdint.h>
#include <sqlite3.h>
#include <hash.h>

#define N 10000

int main(int argc, char **argv)
{
  sqlite3 *conn = NULL;
  int32_t i, hash;
  int exitCode = -1;
  char query[90],
      *dbPath = "database.db",
      *errMsg = NULL;

  exitCode = sqlite3_open(dbPath, &conn);
  if (exitCode)
  {
    fprintf(stderr, "Connection to database failed\n");
    goto cleanup;
  }

  exitCode = sqlite3_exec(conn, "DROP TABLE IF EXISTS tb_c_serial; CREATE TABLE tb_c_serial "
                                "(id INTEGER PRIMARY KEY AUTOINCREMENT, hash INTEGER NOT NULL)",
                          0, 0, &errMsg);
  if (exitCode)
  {
    fprintf(stderr, "%s\n", errMsg);
    goto cleanup;
  }
  sqlite3_free(errMsg);
  errMsg = NULL;

  for (i = 1; i <= N; i++)
  {
    hash = hash32(i);
    snprintf(query, 90, "INSERT INTO tb_c_serial(hash) VALUES (%d);", hash);

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
  if (conn)
    sqlite3_close(conn);

  return exitCode;
}
