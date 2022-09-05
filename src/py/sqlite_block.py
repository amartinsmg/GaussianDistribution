from gaussian import gaussianCDF
from os.path import dirname
from sqlite3 import connect

dbPath = dirname(__file__) + '/../../sqlite/database.db'
query = ''
conn = connect(dbPath)
cur = conn.cursor()
cur.executescript('''DROP TABLE IF EXISTS py_block; CREATE TABLE py_block(id INTEGER PRIMARY KEY
AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);''')

for i in range(-500, 501):
	x = i / 100
	prob = gaussianCDF(0, 1, x)
	query += f'INSERT INTO py_block(z_score, cumulative_distribution) VALUES ({x:.2f}, {prob:.6f});'

cur.executescript(query)
conn.close()
