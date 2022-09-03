#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "gaussian.h"

int main(int argc, char **argv)
{
  MYSQL *conn = mysql_init(NULL);
  int exitCode, i;
  double x, prob;
  char query[90];
  if (mysql_real_connect(conn, "localhost", "root", "root123", "gaussian", 3306, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
  {
    fprintf(stderr, "Connection to database failed: %s\n", mysql_error(conn));
    exit(-1);
  }
  exitCode = mysql_query(conn, "DROP TABLE IF EXISTS c_serial; CREATE TABLE c_serial(id INTEGER AUTO_INCREMENT "
                               "PRIMARY KEY, z_score FLOAT NOT NULL, cumulative_distribution FLOAT NOT NULL)");
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
    sprintf(query, "INSERT INTO c_serial(z_score, cumulative_distribution) VALUES (%.2f, %f)", x, prob);
    exitCode = mysql_query(conn, query);
    if (exitCode)
    {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(-1);
    }
    mysql_next_result(conn);
  }
  mysql_close(conn);
  return 0;
}