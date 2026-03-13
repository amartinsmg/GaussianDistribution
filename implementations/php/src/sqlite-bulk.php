<?php

include "hashes.php";

try {
    $dbPath = sprintf("sqlite:%s/../database.db", dirname(__FILE__));
    $conn = new PDO($dbPath);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $conn->exec(<<<HEREA
            DROP TABLE IF EXISTS tb_php_bulk;
            CREATE TABLE tb_php_bulk
            (id INTEGER PRIMARY KEY AUTOINCREMENT,
            hash INTEGER NULL);
            HEREA);

    $query = "INSERT INTO tb_php_bulk(hash) VALUES ";

    for ($i = 1; $i <= 10000; $i++) {
        $hash = hash32($i);
        $query .= sprintf("(%d),", $hash);
    }

    $query = rtrim($query, ",");

    $conn->beginTransaction();
    $conn->exec($query);
    $conn->commit();
} catch (\Throwable $th) {
    echo $th->getMessage() . "\n";
} finally {
    $conn = null;
}
