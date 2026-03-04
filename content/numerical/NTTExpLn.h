/**
 * Author: Jelefy
 * Date: 2025-10-29
 * License: CC0
 * Description: NTT ln, exp, and pow.
 */
#pragma once

#include "NTTInv.h"

namespace polynomial {
	poly getln(const poly &A) {
		int n = A.size(); poly B(n - 1);
		rep(i,1,n) B[i - 1] = mul(A[i], i);
		B = B * getinv(A); B.resize(n);
		for (int i = n - 1; i; i--) B[i] = mul(B[i - 1], qpow(i));
		B[0] = 0; return B;
	}
	poly getexp(const poly &A) {
		int n = A.size(); if (n == 1) return poly(0, 1);
		poly B = getexp(A.copyas((n + 1) >> 1));
		B.resize(n); poly C = getln(B);
		rep(i,0,n) C[i] = dec(A[i], C[i]); ++C[0];
		C = B * C; C.resize(n); return C;
	}
	poly getpow(poly A, int k) { // ONLY SUPPORTS A0 != 0
		int n = A.size(), A0k = qpow(A[0], k), IA0 = qpow(A[0]);
		for (unsigned &x : A) x = mul(x, IA0); A = getln(A);
		for (unsigned &x : A) x = mul(x, k); A = getexp(A);
		for (unsigned &x : A) x = mul(x, A0k); return A;
	} // k only need to mod mod (not mod-1)
}
