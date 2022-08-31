from gaussian import gaussianCDF
import os
import sqlite3

if __name__ == '__main__':
	databasePath = os.path.dirname(__file__) + '/../../sqlite/database.db'
	db = sqlite3.connect(databasePath)
	db.executescript('''DROP TABLE IF EXISTS py_serial; CREATE TABLE py_serial(id INTEGER PRIMARY KEY
	AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL);''')

	for i in range(-500, 501):
		x = i / 100
		cumulativeD = gaussianCDF(0, 1, x)
		db.execute(
			f'INSERT INTO py_serial(z_score, cumulative_distribution) VALUES ({x:.2f}, {cumulativeD:.6f})')

	db.commit()
	db.close()
