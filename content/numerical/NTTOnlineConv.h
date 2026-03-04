/**
 * Author: Jelefy
 * Date: 2025-10-29
 * License: CC0
 * Description: NTT online convolution, i.e. computes $B_i=\sum_{j=1}^i B_{i-j}A_j$.
 */
#pragma once

#include "NTTInv.h"

namespace polynomial {
	poly onlineconv(poly A, unsigned B0) {
		for (unsigned &x : A) if (x) x = mod - x; A[0] = 1;
		A = getinv(A); for (unsigned &x : A) x = mul(x, B0);
		return A;
	}
}
