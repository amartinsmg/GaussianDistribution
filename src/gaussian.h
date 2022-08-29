#define PI 3.141592653589793

double gaussianCDF(double x, double mean, double standadDev)
{
  double phi, result, z, denominator = 1,
                         sum = 0;
  int i;
  assert(standadDev > 0);
  z = (x - mean) / standadDev;
  phi = exp(-pow(z, 2) / 2) / sqrt(2 * PI);
  for (i = 1; i <= 100; i += 2)
  {
    denominator *= i;
    sum += pow(z, i) / denominator;
  }
  result = 0.5 + phi * sum;
  return result;
}
