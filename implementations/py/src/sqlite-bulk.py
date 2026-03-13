from hashes import hash32
from contextlib import closing
from pathlib import Path
from sqlite3 import connect

dbPath = Path(__file__).parent.parent / "database.db"

try:
    with closing(connect(dbPath)) as conn:
        with conn:
            conn.executescript(
                """DROP TABLE IF EXISTS tb_py_bulk;
                CREATE TABLE tb_py_bulk
                (id INTEGER PRIMARY KEY AUTOINCREMENT,
                hash INTEGER NOT NULL);"""
            )
            conn.commit()

            buf = []
            for i in range(1, 10_001):
                hash = hash32(i)
                buf.append(f"({hash})")

            query = (
                "BEGIN;\nINSERT INTO tb_py_bulk(hash) VALUES "
                + ",".join(buf)
                + ";\nCOMMIT;"
            )
            conn.executescript(query)

except Exception as e:
    print(e)
