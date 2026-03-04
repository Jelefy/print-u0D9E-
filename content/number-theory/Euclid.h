/**
 * Author: Jelefy
 * Date: 2025-12-21
 * Source: augmented based on kactl
 * Description: Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$.
 * Ensure that $a$, $b$, $n$, and $p$ are positive and {\tt type} is a signed integer type.
 */
#pragma once

template<class type> // results satisfy |x| <= b, |y| <= a
type euclid(type a, type b, type &x, type &y) {
	if (!b) return x = 1, y = 0, a;
	type d = euclid(b, a % b, y, x); return y -= a / b * x, d;
}
template<class type>
type getinv(type n, type p) {
	type x = 0, y = 0; if (euclid(n, p, x, y) != 1) return -1;
	return x < 0 ? x + p : x;
}
