<?php

include "hashes.php";

try {
    $conn = new PDO("pgsql:host=127.0.0.1;port=5432;dbname=hashes", "root", "root123");
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $conn->exec(<<<HEREA
            DROP TABLE IF EXISTS tb_php_serial;
            CREATE TABLE tb_php_serial
            (id SERIAL PRIMARY KEY,
            hash INTEGER NULL);
            HEREA);

    for ($i = 1; $i <= 10000; $i++) {
        $hash = hash32($i);
        $query = sprintf("INSERT INTO tb_php_serial(hash) VALUES (%d);", $hash);
        $conn->query($query);
    }
} catch (\Throwable $th) {
    if ($conn->inTransaction()) $conn->rollBack();
    echo $th->getMessage();
} finally {
    $conn = null;
}
