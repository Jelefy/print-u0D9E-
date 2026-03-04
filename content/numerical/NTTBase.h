/**
 * Author: Jelefy
 * Date: 2025-10-29
 * License: CC0
 * Description: Basic NTT without extra utils.
 */
#pragma once

const int mod = 998244353; const unsigned G = 62;
// 62 also fits 5<<25, 7<<26, 479<<21, 483<<21. Last two > 1e9.
namespace polynomial {
	int add(int x, int y) { x+=y; y=x-mod; return y<0 ? x : y; }
	int dec(int x, int y) { x -= y; return x < 0 ? x + mod : x; }
	int mul(int x, int y) { return 1ll * x * y % mod; }
	unsigned qpow(unsigned a, int b = mod - 2) {
		unsigned res = 1;
		for (; b; b >>= 1, a = mul(a, a))
			if (b & 1) res = mul(res, a);
		return res;
	}
	vector<unsigned> w, w_mf;
	int mf(int x) { return (1ll * x << 32) / mod; }
	int bceil(int n){ int L = 1; while(L < n) L *= 2; return L; }
	int init(int n) {
		int L = bceil(n); w.resize(L); w_mf.resize(L);
		unsigned pr = qpow(G, (mod - 1) / L);
		w[L / 2] = 1; w_mf[L / 2] = mf(1);
		rep(i,1,L/2) {
			w[L / 2 + i] = mul(w[L / 2 + i - 1], pr);
			w_mf[L / 2 + i] = mf(w[L / 2 + i]);
		}
		for (int i = L / 2 - 1; i > 0; i--)
			w[i] = w[i << 1], w_mf[i] = w_mf[i << 1];
		return L;
	}
	void ntt(vector<unsigned> &A, int L) {
		for (int d = L >> 1; d; d >>= 1)
			for (int i = 0; i < L; i += (d << 1))
				rep(j,0,d) {
					unsigned x = A[i + j] + A[i + d + j];
					if (x >= 2 * mod) x -= 2 * mod;
					ll t = A[i + j] + 2 * mod - A[i + d + j];
					ll q = t * w_mf[d + j] >> 32;
					int y = t * w[d + j] - q * mod;
					A[i + j] = x; A[i + d + j] = y;
				}
		rep(i,0,L) if (A[i] >= mod) A[i] -= mod;
	}
	void intt(vector<unsigned> &A, int L) {
		for (int d = 1; d < L; d <<= 1)
			for (int i = 0; i < L; i += (d << 1))
				for (int j = 0; j < d; j++) {
					unsigned x = A[i + j];
					if (x >= 2 * mod) x -= 2 * mod;
					ll t = A[i + d + j], q = t * w_mf[d + j] >> 32;
					ll y = t * w[d + j] - q * mod;
					A[i + j] = x + y; A[i + d + j] = x + 2 * mod - y;
				}
		int k = (L & (-L)); reverse(A.begin() + 1, A.end());
		for (int i = 0; i < L; i++) {
			ll m = -A[i] & (L - 1); A[i] = (A[i] + m * mod) / k;
			if (A[i] >= mod) A[i] -= mod;
		}
	}
	struct poly : vector<unsigned> {
		poly(int d = 0, int t = 0) : vector(d + 1) { at(d) = t; }
		poly(vector &&v) : vector(forward<vector>(v)) {}
		void resize(int n) { reserve(n); vector::resize(n); }
		poly copyas(int n) const {
			if (n <= size()) return vector(begin(), begin() + n);
			vector b(n); copy(begin(), end(), b.begin()); return b;
		}
		int deg() const { return size() - 1; }
		void rev() { reverse(begin(), end()); }
	};
	poly nconv(const poly &A, const poly &B) {
		poly C(A.deg() + B.deg());
		rep(i,0,A.size()) rep(j,0,B.size())
		C[i + j] = add(C[i + j], mul(A[i], B[j])); return C;
	}
	poly operator*(const poly &_A, const poly &_B) {
		if(min(_A.size(), _B.size()) <= 60) return
			_A.size() > _B.size() ? nconv(_A, _B) : nconv(_B, _A);
		int n = _A.deg() + _B.deg() + 1, L = init(n);
		poly A = _A.copyas(L), B = _B.copyas(L);
		ntt(A, L); ntt(B, L); rep(i,0,L) A[i] = mul(A[i], B[i]);
		intt(A, L); A.resize(n); return A;
	}
	poly operator-(const poly &A, const poly &B) {
		poly C = A.copyas(max(A.size(), B.size()));
		rep(i,0,B.size()) C[i] = dec(C[i], B[i]); return C;
	} // for + replace dec with add
}
using polynomial::poly;
