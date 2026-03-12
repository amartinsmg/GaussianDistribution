#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libpq-fe.h>
#include <hash.h>

#define N 10000

int main(int argc, char **argv)
{
  PGconn *conn = PQconnectdb("host=127.0.0.1 user=root password=root123 dbname=hashes");
  PGresult *res = NULL;
  int32_t i, hash;
  int exitCode = -1;
  char query[90];

  if (PQstatus(conn) == CONNECTION_BAD)
  {
    fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
    goto cleanup;
  }

  res = PQexec(conn, "DROP TABLE IF EXISTS tb_c_serial; CREATE TABLE tb_c_serial "
                     "(id SERIAL PRIMARY KEY, hash INTEGER NOT NULL)");
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
    snprintf(query, 90, "INSERT INTO tb_c_serial(hash) VALUES (%d)", hash);

    res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
      fprintf(stderr, "%s\n", PQerrorMessage(conn));
      goto cleanup;
    }
    PQclear(res);
    res = NULL;
  }

  exitCode = 0;

cleanup:
  if (res)
    PQclear(res);
  if (conn)
    PQfinish(conn);

  return exitCode;
}
