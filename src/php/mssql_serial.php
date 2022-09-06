<?php

include "gaussian.php";

try {
  $conn = new PDO("sqlsrv:Server=localhost;Database=gaussian", "sa", "root123%");
  $query = "";
  $conn->exec("DROP TABLE IF EXISTS php_serial; CREATE TABLE php_serial(id INT IDENTITY  
  PRIMARY KEY, z_score FLOAT NOT NULL, cumulative_distribution FLOAT NOT NULL)");
  
  for ($i = -500; $i <= 500; $i++) {
    $x = $i / 100;
    $prob = gaussianCDF(0, 1, $x);
    $query = sprintf("INSERT INTO php_serial(z_score, cumulative_distribution) VALUES (%.2f, %f);", $x, $prob);
    $conn->exec($query);
  }
} catch (\Throwable $th) {
  echo $th->getMessage();
}
