/**
 * Author: Jelefy
 * Date: 2025-12-21
 * License: CC0
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "Euclid.h"

const int mod = 998244353; // change to something else
struct Mod {
	int x; Mod() = default;
	template<class type> Mod(type x) : x(x) {}
	Mod &operator+=(Mod b) { x += b.x; if (x >= mod) x -= mod; return *this; }
	Mod operator+(Mod b) const { return b += *this; }
	Mod &operator-=(Mod b) { x -= b.x; if (x < 0) x += mod; return *this; }
	Mod operator-(Mod b) const { b.x = x - b.x; if (b.x < 0) b.x += mod; return b; }
	Mod &operator*=(Mod b) { x =(ll)x * b.x % mod; return *this; }
	Mod operator*(Mod b) const { return b *= *this; }
	Mod inv() const { return getinv(x, mod); }
	Mod &operator/=(Mod b) { *this *= b.inv(); return *this; }
	Mod operator/(Mod b) const { return *this * b.inv(); }
};
