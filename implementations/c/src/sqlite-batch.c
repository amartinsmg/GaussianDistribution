#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <stdint.h>
#include <sqlite3.h>
#include <hash.h>

#define N 10000
#define QUERY_SIZE 600000

int main(int argc, char **argv)
{
  sqlite3 *conn = NULL;
  int32_t i, hash;
  int exitCode = -1,
      buffer = 0;
  char *dbPath = "database.db",
       *query = malloc(QUERY_SIZE * sizeof(*query)),
       *errMsg = NULL;

  if (!query)
  {
    fprintf(stderr, "Failed to allocate query buffer\n");
    goto cleanup;
  }

  exitCode = sqlite3_open(dbPath, &conn);
  if (exitCode)
  {
    fprintf(stderr, "Connection to database failed\n");
    goto cleanup;
  }

  exitCode = sqlite3_exec(conn, "DROP TABLE IF EXISTS tb_c_batch; CREATE TABLE tb_c_batch(id "
                                "INTEGER PRIMARY KEY AUTOINCREMENT, hash INTEGER NOT NULL)",
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
    buffer += snprintf(
        (char *)(query + buffer),
        QUERY_SIZE - buffer,
        "INSERT INTO tb_c_batch(hash) VALUES (%d);",
        hash);
  }

  exitCode = sqlite3_exec(conn, "BEGIN;", 0, 0, &errMsg);
  if (exitCode)
  {
    fprintf(stderr, "%s\n", errMsg);
    goto cleanup;
  }
  sqlite3_free(errMsg);
  errMsg = NULL;

  exitCode = sqlite3_exec(conn, query, 0, 0, &errMsg);
  if (exitCode)
  {
    fprintf(stderr, "%s\n", errMsg);
    goto cleanup;
  }
  sqlite3_free(errMsg);
  errMsg = NULL;

  exitCode = sqlite3_exec(conn, "COMMIT;", 0, 0, &errMsg);
  if (exitCode)
  {
    fprintf(stderr, "%s\n", errMsg);
    goto cleanup;
  }

  exitCode = 0;

cleanup:
  free(query);
  sqlite3_free(errMsg);
  if (conn)
    sqlite3_close(conn);

  return exitCode;
}
