#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "gaussian.h"

int main(int argc, char **argv)
{
  PGconn *conn = PQconnectdb("user=root password=root123 dbname=gaussian");
  PGresult *res = NULL;
  int i, buffer = 0, exitCode = -1;
  double x, prob;
  char *query = (char *)malloc(90000 * sizeof(*query));
  if (query == NULL)
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
  res = PQexec(conn, "DROP TABLE IF EXISTS tb_c_block; CREATE TABLE tb_c_block(id SERIAL PRIMARY KEY, "
                     "z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "%s\n", PQerrorMessage(conn));
    goto cleanup;
  }
  PQclear(res);
  res = NULL;
  for (i = -500; i <= 500; i++)
  {
    x = (double)i / 100.0;
    prob = gaussianCDF(0, 1, x);
    buffer += sprintf((char *)(query + buffer), "INSERT INTO tb_c_block(z_score, cumulative_distribution) VALUES (%.2f, %f);", x, prob);
  }
  res = PQexec(conn, query);
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "%s\n", PQerrorMessage(conn));
    goto cleanup;
  }
  exitCode = 0;

cleanup:
  if (res != NULL)
    PQclear(res);
  free(query);
  PQfinish(conn);
  return exitCode;
}
