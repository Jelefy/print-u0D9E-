/**
 * Author: Jelefy
 * Date: 2025-10-29
 * License: CC0
 * Description: NTT multi-point evaluation.
 * Time: O(N \log^2 N)
 */
#pragma once

#include "NTTInv.h"

namespace polynomial {
	namespace evaluation {
		vector<poly> g; typedef vector<unsigned> vec;
		poly mul_t(const poly &A, poly B) {
			B.rev(); B = A * B;
			return vector<unsigned>(B.end() - A.size(), B.end());
		}
		void eval_init(const vec &a, int i, int l, int r) {
			if (l == r) {g[i] = vec{1, a[l] ? mod-a[l] : 0}; return;}
			int mid = (l + r) >> 1, le = i << 1, ri = i << 1 | 1;
			eval_init(a, le, l, mid), eval_init(a, ri, mid + 1, r);
			g[i] = g[le] * g[ri];
		}
		void eval_work(poly A, auto &v, int i, int l, int r) {
			if (l == r) { v[l] = A[0]; return; } A.resize(r - l + 1);
			int mid = (l + r) >> 1, le = i << 1, ri = i << 1 | 1;
			eval_work(mul_t(A, g[ri]), v, le, l, mid);
			eval_work(mul_t(A, g[le]), v, ri, mid + 1, r);
		}
		vector<unsigned> eval(poly A, vector<unsigned> a) {
			int n = max(A.size(), a.size()), L = bceil(n);
			A.resize(n + 1); a.resize(n); g.resize(L << 1);
			eval_init(a, 1, 0, n - 1); vector<unsigned> v(n);
			eval_work(mul_t(A, getinv(g[1])), v, 1, 0, n - 1);
			return v;
		}
	}
	using evaluation::eval;
}
