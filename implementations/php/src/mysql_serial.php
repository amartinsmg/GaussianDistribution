<?php

include "hashes.php";

try {
    $conn = new PDO("mysql:host=127.0.0.1;port=3306;dbname=hashes", "root", "root123");
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $conn->exec(<<<HEREA
            DROP TABLE IF EXISTS tb_php_serial;
            CREATE TABLE tb_php_serial
            (id INTEGER AUTO_INCREMENT PRIMARY KEY,
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
