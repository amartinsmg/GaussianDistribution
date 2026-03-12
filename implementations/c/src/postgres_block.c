#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libpq-fe.h>
#include <hash.h>

#define N 10000
#define QUERY_SIZE 600000

int main(int argc, char **argv)
{
  PGconn *conn = PQconnectdb("host=127.0.0.1 user=root password=root123 dbname=hashes");
  PGresult *res = NULL;
  int32_t i, hash;
  int buffer = 0,
      exitCode = -1;
  char *query = malloc(QUERY_SIZE * sizeof(*query));

  if (!query)
  {
    fprintf(stderr, "Failed to allocate query buffer\n");
    goto cleanup;
  }

  if (PQstatus(conn) == CONNECTION_BAD)
  {
    fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
    goto cleanup;
  }

  res = PQexec(conn, "DROP TABLE IF EXISTS tb_c_block; CREATE TABLE tb_c_block"
                     "(id SERIAL PRIMARY KEY, hash INTEGER NOT NULL)");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "%s\n", PQerrorMessage(conn));
    goto cleanup;
  }
  PQclear(res);
  res = NULL;

  res = PQexec(conn, "BEGIN;");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "%s\n", PQerrorMessage(conn));
    goto cleanup;
  }
  PQclear(res);
  res = NULL;

  for (i = 1; i <= N; i++)
  {
    hash = hash32(i);
    buffer += snprintf(
        (char *)(query + buffer),
        QUERY_SIZE - buffer,
        "INSERT INTO tb_c_block(hash) VALUES (%d);",
        hash);
  }

  res = PQexec(conn, query);
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "%s\n", PQerrorMessage(conn));
    goto cleanup;
  }
  exitCode = 0;

  res = PQexec(conn, "COMMIT;");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "%s\n", PQerrorMessage(conn));
    goto cleanup;
  }
  PQclear(res);
  res = NULL;

cleanup:
  free(query);
  if (res)
    PQclear(res);
  if (conn)
    PQfinish(conn);

  return exitCode;
}
