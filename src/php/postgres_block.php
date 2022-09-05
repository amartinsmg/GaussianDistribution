<?php

include "gaussian.php";

$conn = new PDO("pgsql:host=localhost;port=5432;dbname=gaussian", "root", "root123");
$query = "";
$conn->exec("DROP TABLE IF EXISTS php_block; CREATE TABLE php_block(id SERIAL PRIMARY KEY, 
z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");

for ($i = -500; $i <= 500; $i++) {
  $x = $i / 100;
  $prob = gaussianCDF(0, 1, $x);
  $query .= sprintf("INSERT INTO php_block(z_score, cumulative_distribution) VALUES (%.2f, %f);", $x, $prob);
}

$conn->exec($query);