<?php

include "gaussian.php";

$conn = new PDO("pgsql:host=localhost;port=5432;dbname=gaussian", "root", "root123");
$conn->exec("DROP TABLE IF EXISTS php_serial; CREATE TABLE php_serial(id SERIAL PRIMARY KEY, 
z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");

for ($i = -500; $i <= 500; $i++) {
  $x = $i / 100;
  $prob = gaussianCDF(0, 1, $x);
  $query = sprintf("INSERT INTO php_serial(z_score, cumulative_distribution) VALUES (%.2f, %f);", $x, $prob);
  $conn->exec($query);
}
