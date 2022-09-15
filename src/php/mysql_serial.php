<?php

include "gaussian.php";

try {
  $conn = new mysqli("localhost", "root", "root123", "gaussian", 3306);
  $conn->multi_query("DROP TABLE IF EXISTS tb_php_serial; CREATE TABLE tb_php_serial(id INTEGER AUTO_INCREMENT
  PRIMARY KEY, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");
  for ($i = -500; $i <= 500; $i++) {
    $x = $i / 100;
    $prob = gaussianCDF(0, 1, $x);
    $conn->next_result();
    $query = sprintf("INSERT INTO tb_php_serial(z_score, cumulative_distribution) VALUES (%.2f, %f);", $x, $prob);
    $conn->query($query);
  }
  $conn->close();  
} catch (\Throwable $th) {
  echo $th->getMessage();
}
