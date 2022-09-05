from gaussian import gaussianCDF
from mysql.connector import connect

conn = connect(
  host="localhost",
  user="root",
  password="root123",
  database="gaussian",
)
cur = conn.cursor()
cur.execute('''DROP TABLE IF EXISTS py_serial; CREATE TABLE py_serial(id INTEGER AUTO_INCREMENT
PRIMARY KEY, z_score FLOAT NOT NULL, cumulative_distribution FLOAT NOT NULL);''')

for i in range(-500, 501):
	x = i / 100
	prob = gaussianCDF(0, 1, x)
	conn.next_result()
	cur.execute(
		f'INSERT INTO py_serial(z_score, cumulative_distribution) VALUES ({x:.2f}, {prob:.6f})')

conn.close()
