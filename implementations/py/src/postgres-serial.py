from hashes import hash32
from psycopg2 import connect

try:
    with connect(
        host="127.0.0.1",
        user="root",
        password="root123",
        database="hashes",
    ) as conn:
        with conn.cursor() as cur:
            cur.execute(
                """DROP TABLE IF EXISTS tb_py_serial;
                CREATE TABLE tb_py_serial
                (id SERIAL PRIMARY KEY,
                hash INTEGER NOT NULL);"""
            )
            conn.commit()

            for i in range(1, 10_001):
                hash = hash32(i)
                cur.execute("INSERT INTO tb_py_serial(hash) VALUES (%s)", (hash,))
                conn.commit()

except Exception as e:
    print(e)
