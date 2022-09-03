#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "gaussian.h"

int main(int argc, char **argv)
{
  PGconn *conn = PQconnectdb("user=root password=root123 dbname=gaussian");
  PGresult *res;
  int i;
  double x, prob;
  char query[90];
  if (PQstatus(conn) == CONNECTION_BAD)
  {
    fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
    exit(-1);
  }
  res = PQexec(conn, "DROP TABLE IF EXISTS c_serial; CREATE TABLE c_serial(id SERIAL PRIMARY KEY, "
                     "z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "%s\n", PQerrorMessage(conn));
    exit(-1);
  }
  for (i = -500; i <= 500; i++)
  {
    x = (double)i / 100.0;
    prob = gaussianCDF(0, 1, x);
    sprintf(query, "INSERT INTO c_serial(z_score, cumulative_distribution) VALUES (%.2f, %f)", x, prob);
    res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
      fprintf(stderr, "%s\n", PQerrorMessage(conn));
      exit(-1);
    }
  }
  PQfinish(conn);
  return 0;
}