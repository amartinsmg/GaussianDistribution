<?php

function gaussianCDF($x, $mean, $standadDev)
{
  $denominator = 1;
  $sum = 0;
  assert($standadDev > 0);
  $z = ($x - $mean) / $standadDev;
  $phi = exp(-pow($z, 2) / 2) / sqrt(2 * M_PI);
  for ($i = 1; $i <= 100; $i += 2) {
    $denominator *= $i;
    $sum += pow($z, $i) / $denominator;
  }
  $result = 0.5 + $phi * $sum;
  return $result;
}
