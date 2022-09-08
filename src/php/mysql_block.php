<?php

include "gaussian.php";

try {
  $conn = new mysqli("localhost", "root", "root123", "gaussian", 3306);
  $query = "";
  $conn->multi_query("DROP TABLE IF EXISTS php_block; CREATE TABLE php_block(id INTEGER AUTO_INCREMENT
  PRIMARY KEY, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)");
  for ($i = -500; $i <= 500; $i++) {
    $x = $i / 100;
    $prob = gaussianCDF(0, 1, $x);
    $query .= sprintf("INSERT INTO php_block(z_score, cumulative_distribution) VALUES (%.2f, %f);", $x, $prob);
  }
  $conn->next_result();
  $conn->multi_query($query);
  $conn->close();
} catch (\Throwable $th) {
  echo $th->getMessage();
}
