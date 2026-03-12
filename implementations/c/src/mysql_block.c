#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mysql.h>
#include <hash.h>

#define N 10000
#define QUERY_SIZE 600000

void clear_mysql_results(MYSQL *conn)
{
  MYSQL_RES *res;
  while (mysql_next_result(conn) == 0)
  {
    res = mysql_store_result(conn);
    if (res)
      mysql_free_result(res);
  }
}

int main(int argc, char **argv)
{
  MYSQL *conn = mysql_init(NULL);
  int32_t i, hash;
  int exitCode = -1,
      buffer = 0;
  double x, prob;
  char *query = malloc(QUERY_SIZE * sizeof(*query));

  if (!conn)
  {
    fprintf(stderr, "Failed to initialize MySQL connection object\n");
    goto cleanup;
  }

  if (!query)
  {
    fprintf(stderr, "Failed to allocate query buffer\n");
    goto cleanup;
  }

  if (!mysql_real_connect(conn, "127.0.0.1", "root", "root123", "hashes", 3306, NULL, CLIENT_MULTI_STATEMENTS))
  {
    fprintf(stderr, "Connection to database failed: %s\n", mysql_error(conn));
    goto cleanup;
  }

  exitCode = mysql_query(conn, "DROP TABLE IF EXISTS tb_c_batch; CREATE TABLE tb_c_batch "
                             "(id INTEGER AUTO_INCREMENT PRIMARY KEY, hash INTEGER NOT NULL)");
  if (exitCode)
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    goto cleanup;
  }
  clear_mysql_results(conn);

  for (i = 1; i <= N; i++)
  {
    hash = hash32(i);
    buffer += snprintf(
        (char *)(query + buffer),
        QUERY_SIZE - buffer,
        "INSERT INTO tb_c_batch(hash) VALUES (%d);",
        hash);
  }

  exitCode = mysql_query(conn, "BEGIN; ");
  if (exitCode)
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    goto cleanup;
  }
  clear_mysql_results(conn);

  exitCode = mysql_query(conn, query);
  if (exitCode)
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    goto cleanup;
  }
  clear_mysql_results(conn);

  exitCode = mysql_query(conn, "COMMIT; ");
  if (exitCode)
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    goto cleanup;
  }
  clear_mysql_results(conn);

  exitCode = 0;

cleanup:
  free(query);
  if (conn)
    mysql_close(conn);

  mysql_library_end();

  return exitCode;
}
