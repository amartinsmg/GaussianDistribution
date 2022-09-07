#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "gaussian.h"

int main(int argc, char **argv)
{
  MYSQL *conn = mysql_init(NULL);
  int exitCode, i, buffer = 0;
  double x, prob;
  char *query = (char *)malloc(90000 * sizeof(*query));
  if (mysql_real_connect(conn, "localhost", "root", "root123", "gaussian", 3306, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
  {
    fprintf(stderr, "Connection to database failed: %s\n", mysql_error(conn));
    exit(-1);
  }
  exitCode = mysql_query(conn, "DROP TABLE IF EXISTS c_block; CREATE TABLE c_block(id INTEGER AUTO_INCREMENT "
                               "PRIMARY KEY, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");
  if (exitCode)
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(-1);
  }
  mysql_next_result(conn);
  for (i = -500; i <= 500; i++)
  {
    x = (double)i / 100.0;
    prob = gaussianCDF(0, 1, x);
    buffer += sprintf((char *)(query + buffer), "INSERT INTO c_block(z_score, cumulative_distribution) VALUES (%.2f, %f);", x, prob);
  }
  exitCode = mysql_query(conn, query);
  if (exitCode)
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(-1);
  }
  mysql_close(conn);
  return 0;
}