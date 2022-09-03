from gaussian import gaussianCDF
import os
import sqlite3

dbPath = os.path.dirname(__file__) + '/../../sqlite/database.db'
conn = sqlite3.connect(dbPath)
conn.executescript('''DROP TABLE IF EXISTS py_serial; CREATE TABLE py_serial(id INTEGER PRIMARY KEY
AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);''')

for i in range(-500, 501):
	x = i / 100
	prob = gaussianCDF(0, 1, x)
	conn.execute(
		f'INSERT INTO py_serial(z_score, cumulative_distribution) VALUES ({x:.2f}, {prob:.6f})')

conn.commit()
conn.close()
