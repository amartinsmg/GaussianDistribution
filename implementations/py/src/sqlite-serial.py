from hashes import hash32
from pathlib import Path
from sqlite3 import connect

dbPath = Path(__file__).parent.parent / "database.db"

try:
    conn = connect(dbPath, autocommit=True)
    cur = conn.cursor()
    cur.executescript(
        """DROP TABLE IF EXISTS tb_py_serial;
        CREATE TABLE tb_py_serial
        (id INTEGER PRIMARY KEY AUTOINCREMENT,
        hash INTEGER NOT NULL);"""
    )

    for i in range(1, 10_001):
        hash = hash32(i)
        cur.execute("INSERT INTO tb_py_serial(hash) VALUES (?)", (hash,))

except Exception as e:
    print(e)

finally:
    if conn:
        conn.close()
