from hashes import hash32
from mysql.connector import connect

try:
    with connect(
        host="127.0.0.1",
        user="root",
        password="root123",
        database="hashes",
    ) as conn:
        with conn.cursor() as cur:
            cur.execute(
                """DROP TABLE IF EXISTS tb_py_batch;
                CREATE TABLE tb_py_batch
                (id INTEGER AUTO_INCREMENT PRIMARY KEY,
                hash INTEGER NOT NULL);"""
            )
            conn.next_result()
            conn.commit()

            inserts = []
            for i in range(1, 10_001):
                hash = hash32(i)
                inserts.append(f"INSERT INTO tb_py_batch(hash) VALUES ({hash});")

            query = "BEGIN;\n" + "\n".join(inserts) + "\nCOMMIT;"
            cur.execute(query)

except Exception as e:
    print(e)
