const assert = require("assert");

function gaussianCDF(mean, standardDev, x) {
  let phi,
    result,
    z,
    denominator = 1,
    sum = 0;
  assert.ok(standardDev > 0);
  z = (x - mean) / standardDev;
  phi = Math.exp(-(z ** 2) / 2) / Math.sqrt(2 * Math.PI);
  for (let i = 1; i <= 100; i += 2) {
    denominator *= i;
    sum += z ** i / denominator;
  }
  result = 0.5 + phi * sum;
  return result;
}

module.exports = {
  gaussianCDF,
};
