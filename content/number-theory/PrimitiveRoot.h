/**
 * Author: Jelefy
 * Date: 2025-10-30
 * License: CC0
 * Description: Assume $a\perp m$. $a$ is a primitive root of $m$ iff $\delta_m(a)=\varphi(m)$, where $\delta_m(a)$ is the order of $a$ mod $m$, i.e. the minimum $n$ such that $a^n\equiv 1\pmod m$.
 */

#pragma once

int num[N], tot; // N >= number of prime factors of phi
int minroot(int n, int &phi) { // phi init val arbitrary
	if (n == 4) { phi = 2; return 3; }
	if (n == 1 || (!(n & 1) && !(n & 2))) return -1;
	int tmp = (n & 1) ? n : (n >> 1); phi = tmp, tot = 0;
	for (int i = 3; i * i <= tmp; i++) if (tmp % i == 0) {
		if (tot) return -1;
		tot = 1; phi = phi / i * (i - 1);
		do tmp /= i; while (tmp % i == 0);
	}
	if (tmp > 1) {
		if (tot) return -1; else phi = phi / tmp * (tmp - 1);
	}
	tot = 0, tmp = phi;
	for (int i = 2; i * i <= tmp; i++) if (tmp % i == 0) {
		num[tot++] = phi / i; do tmp /= i; while (tmp % i == 0);
	}
	if (tmp > 1) num[tot++] = phi / tmp;
	for (int i = 1, j;; i++) if (gcd(i, n) == 1) {
		for (j = 0; j < tot && fpow(i, num[j], n) != 1; j++);
		if (j == tot) return i;
	}
}
vi getroots(int n) {
	int phi, mn = minroot(n, phi); if (mn == -1) return vi();
	vi roots({mn});
	for (int i = 2, tmp = 1ll * mn * mn % n;
	     i < phi; i++, tmp = 1ll * tmp * mn % n)
		if (gcd(i, phi) == 1) roots.push_back(tmp);
	return roots; // NOT ORDERED!
}
