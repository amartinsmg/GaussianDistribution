<?php
function calculatePi($precision)
{
  $pi = 0.0;
  $k = 1.0;
  $max = pow(10, $precision);
  for ($i = 0; $i < $max; $i++) {
    if ($i % 2 == 0)
      $pi += 4 / $k;
    else
      $pi -= 4 / $k;
    $k += 2;
  }
  return $pi;
}

$pi = calculatePi(9);
printf("Pi = %.8f\n", $pi);
