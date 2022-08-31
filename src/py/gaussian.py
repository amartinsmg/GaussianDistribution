
from math import exp, pi, sqrt


def gaussianCDF(mean, standardDev, x):
	denominator = 1
	sum = 0
	assert standardDev > 0
	z = (x - mean) / standardDev
	phi = exp(-(z ** 2) / 2) / sqrt(2 * pi)
	for i in range(1, 100, 2):
		denominator *= i
		sum += z ** i / denominator
	result = 0.5 + phi * sum
	return result
