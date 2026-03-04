/**
 * Author: Jelefy
 * Date: 2025-10-29
 * License: CC0
 * Description: NTT inversion.
 */
#pragma once

#include "NTTBase.h"

namespace polynomial {
	poly getinv(const poly &_A) {
		int n = _A.size(); if (n == 1) return poly(0, qpow(_A[0]));
		poly B = _A.copyas((n + 1) >> 1); B = getinv(B);
		int L = init(n << 1); poly A = _A.copyas(L); B.resize(L);
		ntt(A, L); ntt(B, L);
		rep(i,0,L) A[i] = mul(dec(2, mul(A[i], B[i])), B[i]);
		intt(A, L); A.resize(n); return A;
	}
}
