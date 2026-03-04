/**
 * Author: Jelefy
 * Date: 2025-10-29
 * License: CC0
 * Description: NTT division and mod.
 */
#pragma once

#include "NTTInv.h"

namespace polynomial {
	poly operator/(poly A, poly B) {
		if (A.deg() < B.deg()) return poly();
		A.rev(), B.rev(); int n = A.size(), m = B.size();
		A.resize(n - m + 1), B.resize(n - m + 1); B = getinv(B);
		A = A * B; A.resize(n - m + 1); A.rev(); return A;
	}
	poly operator%(const poly &A, const poly &B) {
		poly C = B * (A / B); C.resize(A.size());
		C = A - C; C.resize(B.size() - 1); return C;
	}
}
