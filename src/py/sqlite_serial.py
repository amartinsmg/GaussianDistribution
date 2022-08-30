from gaussian import gaussianCDF
import sqlite3
from os import path

if __name__ == '__main__':
    databasePath = path.abspath(path.dirname(
        __file__) + '/../../sqlite/database.db')
    db = sqlite3.connect(databasePath)
    cur = db.cursor()
    cur.executescript('''DROP TABLE IF EXISTS py_serial; CREATE TABLE py_serial(id INTEGER PRIMARY KEY
    AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);''')

    for i in range(-500, 501):
        x = i / 100
        cumulativeD = gaussianCDF(0, 1, x)
        cur.execute(
            f'INSERT INTO py_serial(z_score, cumulative_distribution) VALUES ({x:.2f}, {cumulativeD:.6f})')

    db.commit()
    db.close()
