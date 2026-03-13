<?php

function int32($n)
{
    $n &= 0xffffffff;
    if ($n & 0x80000000) $n -= 0x100000000;
    return $n;
}

function hash32($x)
{
    $x = int32($x);
    $x ^= int32($x >> 16);
    $x = int32($x * 0x7feb352d);
    $x ^= int32($x >> 15);
    $x = int32($x * 0x846ca68d);
    $x ^= int32($x >> 16);
    return int32($x);
}
