from hashes import hash32
from psycopg import connect

try:
    with connect(
        host="127.0.0.1",
        user="root",
        password="root123",
        dbname="hashes",
    ) as conn:
        with conn.cursor() as cur:
            cur.execute(
                """DROP TABLE IF EXISTS tb_py_batch;
                CREATE TABLE tb_py_batch
                (id SERIAL PRIMARY KEY,
                hash INTEGER NOT NULL);"""
            )
            conn.commit()

            buf = []
            for i in range(1, 10_001):
                hash = hash32(i)
                buf.append(f"INSERT INTO tb_py_batch(hash) VALUES ({hash});")

            query = "\n".join(buf)
            cur.execute(query)

except Exception as e:
    print(e)
