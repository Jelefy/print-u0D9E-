/**
 * Author: Jelefy
 * Date: 2025-12-6
 * Source: OI-Wiki
 * Description: Calculate $f=\sum_{i=0}^n\left\lfloor\frac{ai+b}{c}\right\rfloor$,
 * $g=\sum_{i=0}^ni\left\lfloor\frac{ai+b}{c}\right\rfloor$,
 * $h=\sum_{i=0}^n\left\lfloor\frac{ai+b}{c}\right\rfloor^2$.
 * Time: O(\log\min\{a,c,n\})
 */
#pragma once

struct result { int f, g, h; };
result euclid_mimic(ll a, ll b, ll c, ll n) {
	constexpr ll M = mod, i2 = (M + 1) / 2, i6 = (M + 1) / 6;
	ll n2 = (n + 1) * n % M * i2 % M;
	ll n3 = (2 * n + 1) * (n + 1) % M * n % M * i6 % M;
	result res{0, 0, 0};
	if (a >= c || b >= c) {
		result tmp = euclid_mimic(a % c, b % c, c, n);
		ll aa = a / c, bb = b / c;
		res.f = (tmp.f + aa * n2 + bb * (n + 1)) % M;
		res.g = (tmp.g + aa * n3 + bb * n2) % M;
		res.h = (tmp.h + 2 * bb * tmp.f % M + 2 * aa * tmp.g % M +
				 aa * aa % M * n3 % M + bb * bb % M * (n + 1) % M +
				 2 * aa * bb % M * n2 % M) % M;
		return res;
	}
	ll m = (a * n + b) / c; if (!m) return res;
	result tmp = euclid_mimic(c, c - b - 1, a, m - 1);
	res.f = (m * n - tmp.f + M) % M;
	res.g = (m * n2 + (M - tmp.f) * i2 + (M - tmp.h) * i2) % M;
	res.h = (n * m % M * m - tmp.f - tmp.g * 2 + 3 * M) % M;
	return res;
}
