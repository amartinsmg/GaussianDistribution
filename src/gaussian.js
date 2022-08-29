const assert = require("assert");

function gaussianCDF(x, mean, standadDev) {
  let phi,
    result,
    z,
    denominator = 1,
    sum = 0;
  assert.ok(standadDev > 0);
  z = (x - mean) / standadDev;
  phi = Math.exp(-(z ** 2) / 2) / Math.sqrt(2 * Math.PI);
  for (let i = 1; i <= 100; i += 2) {
    denominator *= i;
    sum += z ** i / denominator;
  }
  result = 0.5 + phi * sum;
  return result;
}

module.exports({
  gaussianCDF,
});
