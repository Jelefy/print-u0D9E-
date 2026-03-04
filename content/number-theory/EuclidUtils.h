/**
 * Author: Jelefy
 * Date: 2025-12-21
 * Description: Get bounded solutions for euclid. Ensure that $a$ and $b$ are positive.
 */
#pragma once

#include "Euclid.h"

// solve ax + by = c, find the smallest x
// that >= lo. upper bound of result is lo + b - 1
long long euclidge(int a, int b, int c, int lo) {
	int x = 0, y = 0; int d = euclid(a, b, x, y);
	a /= d, b /= d, c /= d; long long res = 1ll * x * c % b;
	if (res > lo) res -= (res - lo) / b * b;
	if (res < lo) res += (lo - res + b - 1) / b * b;
	return res;
}
// solve ax + by = c, find the greatest x
// that < hi. lower bound of result is hi - b + 1
long long euclidl(int a, int b, int c, int hi) {
	int x = 0, y = 0; int d = euclid(a, b, x, y);
	a /= d, b /= d, c /= d; long long res = 1ll * x * c % b;
	if (res >= hi) res -= (res - hi + b) / b * b;
	if (res + 1 < hi) res += (hi - res - 1) / b * b;
	return res;
}
