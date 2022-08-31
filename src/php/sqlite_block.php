<?php

include "gaussian.php";

$databasePath = dirname(__FILE__) . "/../../sqlite/database.db";
$db = new SQLite3($databasePath);
$query = "";
$db->exec("DROP TABLE IF EXISTS php_block; CREATE TABLE php_block(id INTEGER PRIMARY KEY 
AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");

for ($i = -500; $i <= 500; $i++) {
  $x = $i / 100;
  $cumulativeD = gaussianCDF(0, 1, $x);
  $query .= sprintf("INSERT INTO php_block(z_score, cumulative_distribution) VALUES (%.2f, %f);", $x, $cumulativeD);
}

$db->exec($query);
$db->close();
