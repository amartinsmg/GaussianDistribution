
from math import exp, pi, sqrt


def gaussianCDF(x, mean, standadDev):
    denominator = 1
    sum = 0
    assert (standadDev > 0)
    z = (x - mean) / standadDev
    phi = exp(-pow(z, 2) / 2) / sqrt(2 * pi)
    for i in range(1, 100, 2):
        denominator *= i
        sum += pow(z, i) / denominator
    result = 0.5 + phi * sum
    return result
