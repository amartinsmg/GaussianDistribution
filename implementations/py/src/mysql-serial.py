from hashes import hash32
from mysql.connector import connect

try:
    with connect(
        host="127.0.0.1",
        user="root",
        password="root123",
        database="hashes",
        autocommit=True,
    ) as conn:
        with conn.cursor() as cur:
            cur.execute(
                """DROP TABLE IF EXISTS tb_py_serial;
                CREATE TABLE tb_py_serial
                (id INTEGER AUTO_INCREMENT PRIMARY KEY,
                hash INTEGER NOT NULL);"""
            )
            conn.next_result()

            for i in range(1, 10_001):
                hash = hash32(i)
                cur.execute("INSERT INTO tb_py_serial(hash) VALUES (%s)", (hash,))
                conn.next_result()

except Exception as e:
    print(e)
