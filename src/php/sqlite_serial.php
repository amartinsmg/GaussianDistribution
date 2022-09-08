<?php

include "gaussian.php";

try {
  $dbPath = sprintf("sqlite:%s/../../sqlite/database.db", dirname(__FILE__));
  $conn = new PDO($dbPath);
  $conn->exec("DROP TABLE IF EXISTS php_serial; CREATE TABLE php_serial(id INTEGER PRIMARY KEY 
  AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");
  for ($i = -500; $i <= 500; $i++) {
    $x = $i / 100;
    $prob = gaussianCDF(0, 1, $x);
    $query = sprintf("INSERT INTO php_serial(z_score, cumulative_distribution) VALUES (%.2f, %f);", $x, $prob);
    $conn->exec($query);
  }
} catch (\Throwable $th) {
  echo $th->getMessage();
}
