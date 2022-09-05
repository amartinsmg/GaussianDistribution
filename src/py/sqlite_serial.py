from gaussian import gaussianCDF
from os.path import dirname
from sqlite3 import connect

dbPath = dirname(__file__) + '/../../sqlite/database.db'
conn = connect(dbPath)
cur = conn.cursor()
cur.executescript('''DROP TABLE IF EXISTS py_serial; CREATE TABLE py_serial(id INTEGER PRIMARY KEY
AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);''')

for i in range(-500, 501):
	x = i / 100
	prob = gaussianCDF(0, 1, x)
	cur.execute(
		f'INSERT INTO py_serial(z_score, cumulative_distribution) VALUES ({x:.2f}, {prob:.6f})')

conn.close()
