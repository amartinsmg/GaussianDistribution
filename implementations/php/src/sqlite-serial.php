<?php

include "hashes.php";

try {
    $dbPath = sprintf("sqlite:%s/../database.db", dirname(__FILE__));
    $conn = new PDO($dbPath);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $conn->exec(<<<HEREA
            DROP TABLE IF EXISTS tb_php_serial;
            CREATE TABLE tb_php_serial
            (id INTEGER PRIMARY KEY AUTOINCREMENT,
            hash INTEGER NULL);
            HEREA);

    for ($i = 1; $i <= 10000; $i++) {
        $hash = hash32($i);
        $query = sprintf("INSERT INTO tb_php_serial(hash) VALUES (%d);", $hash);
        $conn->query($query);
    }
} catch (\Throwable $th) {
    echo $th->getMessage() . "\n";
} finally {
    $conn = null;
}
