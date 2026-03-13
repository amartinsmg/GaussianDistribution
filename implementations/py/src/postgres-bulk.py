from hashes import hash32
from psycopg2 import connect

try:
    conn=None
    with connect(
        host="127.0.0.1",
        user="root",
        password="root123",
        database="hashes",
    ) as conn:
        with conn.cursor() as cur:
            cur.execute(
                """DROP TABLE IF EXISTS tb_py_bulk;
                CREATE TABLE tb_py_bulk
                (id SERIAL PRIMARY KEY,
                hash INTEGER NOT NULL);"""
            )
            conn.commit()

            inserts = []
            for i in range(1, 10_001):
                hash = hash32(i)
                inserts.append(f"({hash})")

            query = (
                "BEGIN;\nINSERT INTO tb_py_bulk(hash) VALUES "
                + ",".join(inserts)
                + ";\nCOMMIT;"
            )
            cur.execute(query)

except Exception as e:
    print(e)

