from hashes import hash32
from contextlib import closing
from pathlib import Path
from sqlite3 import connect

dbPath = Path(__file__).parent.parent / "database.db"

try:
    with closing(connect(dbPath, autocommit=True)) as conn:
        conn.executescript(
            """DROP TABLE IF EXISTS tb_py_serial;
            CREATE TABLE tb_py_serial
            (id INTEGER PRIMARY KEY AUTOINCREMENT,
            hash INTEGER NOT NULL);"""
        )

        for i in range(1, 10_001):
            hash = hash32(i)
            conn.execute("INSERT INTO tb_py_serial(hash) VALUES (?)", (hash,))

except Exception as e:
    print(e)
