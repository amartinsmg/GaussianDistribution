from hashes import hash32
from pathlib import Path
from sqlite3 import connect

dbPath = Path(__file__).parent.parent / "database.db"

try:
    conn = connect(dbPath)
    cur = conn.cursor()
    cur.executescript(
        """DROP TABLE IF EXISTS tb_py_bulk;
        CREATE TABLE tb_py_bulk
        (id INTEGER PRIMARY KEY AUTOINCREMENT,
        hash INTEGER NOT NULL);"""
    )

    inserts = []
    for i in range(1, 10_001):
        hash = hash32(i)
        inserts.append(f"({hash})")

    query = (
        "BEGIN;\nINSERT INTO tb_py_bulk(hash) VALUES "
        + ",".join(inserts)
        + ";\nCOMMIT;"
    )
    cur.executescript(query)

except Exception as e:
    print(e)
