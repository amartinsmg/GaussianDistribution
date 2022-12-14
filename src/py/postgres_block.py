from gaussian import gaussianCDF
from psycopg2 import connect

query = ''
try:
	conn = connect(
		host="localhost",
		user="root",
		password="root123",
		database="gaussian",
	)
	conn.autocommit = True
	cur = conn.cursor()
	cur.execute('''DROP TABLE IF EXISTS tb_py_block; CREATE TABLE tb_py_block(id SERIAL PRIMARY KEY,
	z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);''')
	for i in range(-500, 501):
		x = i / 100
		prob = gaussianCDF(0, 1, x)
		query += f'INSERT INTO tb_py_block(z_score, cumulative_distribution) VALUES ({x:.2f}, {prob:.6f});'
	cur.execute(query)
	conn.close()
except Exception as e:
	print(e)
