from gaussian import gaussianCDF
from os.path import dirname
from sqlite3 import connect

dbPath = dirname(__file__) + '/../../sqlite/database.db'
query = ''

try:
	conn = connect(dbPath)
	cur = conn.cursor()
	cur.executescript('''DROP TABLE IF EXISTS tb_py_block; CREATE TABLE tb_py_block(id INTEGER PRIMARY KEY
	AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);''')
	conn.commit()
	for i in range(-500, 501):
		x = i / 100
		prob = gaussianCDF(0, 1, x)
		query += f'INSERT INTO tb_py_block(z_score, cumulative_distribution) VALUES ({x:.2f}, {prob:.6f});'
	cur.executescript(query)
	conn.commit()
	conn.close()
except Exception as e:
	print(e)
