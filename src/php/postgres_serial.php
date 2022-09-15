<?php

include "gaussian.php";

try {
  $conn = new PDO("pgsql:host=localhost;port=5432;dbname=gaussian", "root", "root123");
  $conn->exec("DROP TABLE IF EXISTS tb_php_serial; CREATE TABLE tb_php_serial(id SERIAL PRIMARY KEY, 
  z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");
  for ($i = -500; $i <= 500; $i++) {
    $x = $i / 100;
    $prob = gaussianCDF(0, 1, $x);
    $query = sprintf("INSERT INTO tb_php_serial(z_score, cumulative_distribution) VALUES (%.2f, %f);", $x, $prob);
    $conn->exec($query);
  }
} catch (\Throwable $th) {
  echo $th->getMessage();
}
