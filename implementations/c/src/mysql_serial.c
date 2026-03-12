#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mysql.h>
#include <hash.h>

#define N 10000

int main(int argc, char **argv)
{
  MYSQL *conn = mysql_init(NULL);
  int32_t i, hash;
  int exitCode = -1;
  char query[90];

  if (!conn)
  {
    fprintf(stderr, "Failed to initialize MySQL connection object\n");
    goto cleanup;
  }

  if (!mysql_real_connect(conn, "127.0.0.1", "root", "root123", "hashes", 3306, NULL, CLIENT_MULTI_STATEMENTS))
  {
    fprintf(stderr, "Connection to database failed: %s\n", mysql_error(conn));
    goto cleanup;
  }

  exitCode = mysql_query(conn, "DROP TABLE IF EXISTS tb_c_serial; CREATE TABLE tb_c_serial "
                             "(id INTEGER AUTO_INCREMENT PRIMARY KEY, hash INTEGER NOT NULL)");
  if (exitCode)
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    goto cleanup;
  }
  mysql_next_result(conn);

  for (i = 1; i <= N; i++)
  {
    hash = hash32(i);
    snprintf(query, 90, "INSERT INTO tb_c_serial(hash) VALUES (%d)", hash);

    exitCode = mysql_query(conn, query);
    if (exitCode)
    {
      fprintf(stderr, "%s\n", mysql_error(conn));
      goto cleanup;
    }
    mysql_next_result(conn);
  }

  exitCode = 0;

cleanup:
  if (conn)
    mysql_close(conn);

  mysql_library_end();

  return exitCode;
}
