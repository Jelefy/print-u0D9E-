/**
 * Author: Jelefy
 * Date: 2025-10-31
 * License: CC0
 */
#pragma once

void insert(long long x) {
	for (int i = 62; i >= 0; i--) if (x >> i) {
		if (!p[i]) { p[i] = x; break; } else x ^= p[i];
	}
}
long long query_max() {
	long long x = 0;
	for (int i = 62; i >= 0; i--) if ((x ^ p[i]) > x) x ^= p[i];
	return x;
}
