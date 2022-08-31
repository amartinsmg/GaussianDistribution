<?php

include "gaussian.php";

$databasePath = dirname(__FILE__) . "/../../sqlite/database.db";
$db = new SQLite3($databasePath);
$db->exec("DROP TABLE IF EXISTS php_serial; CREATE TABLE php_serial(id INTEGER PRIMARY KEY 
AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");

for ($i = -500; $i <= 500; $i++) {
  $x = $i / 100;
  $cumulativeD = gaussianCDF(0, 1, $x);
  $query = sprintf("INSERT INTO php_serial(z_score, cumulative_distribution) VALUES (%.2f, %f);", $x, $cumulativeD);
  $db->exec($query);
}

$db->close();
