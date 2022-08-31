public class Gaussian {
  public static double gaussianCDF(double mean, double standardDev, double x) {
    double phi, result, z, denominator = 1,
        sum = 0;
    int i;
    assert (standardDev > 0);
    z = (x - mean) / standardDev;
    phi = Math.exp(-Math.pow(z, 2) / 2) / Math.sqrt(2 * Math.PI);
    for (i = 1; i <= 100; i += 2) {
      denominator *= i;
      sum += Math.pow(z, i) / denominator;
    }
    result = 0.5 + phi * sum;
    return result;
  }
}