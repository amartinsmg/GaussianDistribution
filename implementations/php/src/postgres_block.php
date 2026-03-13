<?php

include "hashes.php";

try {
    $conn = new PDO("pgsql:host=127.0.0.1;port=5432;dbname=hashes", "root", "root123");
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $conn->exec(<<<HEREA
            DROP TABLE IF EXISTS tb_php_batch;
            CREATE TABLE tb_php_batch
            (id SERIAL PRIMARY KEY,
            hash INTEGER NULL);
            HEREA);
    $query = "";

    for ($i = 1; $i <= 10000; $i++) {
        $hash = hash32($i);
        $query .= sprintf("INSERT INTO tb_php_batch(hash) VALUES (%d); ", $hash);
    }

    $conn->beginTransaction();
    $conn->exec($query);
    $conn->commit();
} catch (\Throwable $th) {
    echo $th->getMessage() . "\n";
} finally {
    $conn = null;
}
