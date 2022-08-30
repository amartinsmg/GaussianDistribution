using System;
using System.Diagnostics;

namespace Calc
{
  class Gasussian
  {
    static double GasussianCDF(double mean, double standardDev, double x)
    {
      double phi, result, z, denominator = 1,
        sum = 0;
      int i;
      Debug.Assert(standardDev > 0);
      z = (x - mean) / standardDev;
      phi = Math.Exp(-Math.Pow(z, 2) / 2) / Math.Sqrt(2 * Math.PI);
      for (i = 1; i <= 100; i += 2)
      {
        denominator *= i;
        sum += Math.Pow(z, i) / denominator;
      }
      result = 0.5 + phi * sum;
      return result;
    }
  }
}