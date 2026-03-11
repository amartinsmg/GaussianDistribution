from gaussian import gaussianCDF
from mysql.connector import connect

try:
	conn = connect(
		host="localhost",
		user="root",
		password="root123",
		database="gaussian",
	)
	conn.autocommit = True
	cur = conn.cursor()
	cur.execute('''DROP TABLE IF EXISTS tb_py_serial; CREATE TABLE tb_py_serial(id INTEGER AUTO_INCREMENT
	PRIMARY KEY, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);''')
	for i in range(-500, 501):
		x = i / 100
		prob = gaussianCDF(0, 1, x)
		conn.next_result()
		cur.execute(
			f'INSERT INTO tb_py_serial(z_score, cumulative_distribution) VALUES ({x:.2f}, {prob:.6f})')
	conn.close()
except Exception as e:
	print(e)
