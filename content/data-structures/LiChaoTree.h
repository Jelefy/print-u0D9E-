/**
 * Author: Jelefy
 * Date: 2025-10-29
 * License: CC0
 * Description: Dynamic max LiChao Tree, support merging
 */
#pragma once

// only maintain y coords >= YB, for int mind overflow of -MAX
constexpr double YB = -DBL_MAX;
struct line { // ensure k != inf
	double k{}, b{YB}; int id{}; line() = default;
	line(double k, double b, int id) : k(k), b(b), id(id) {}
	double at(ll x) { return x * k + b; } // mind ovfl for int
	// ensure return type of at() is ytype
	bool operator<(const line &r) const { return id < r.id; }
	// prioritize smaller one; return false if not needed
}; // no worries about overflow inside struct lichao
template <class line, class ytype, ll n>
struct lichao {
	// if ytype is integer, set eps = 0
	static constexpr ytype eps = 1e-9;
	ll P, L, R; line K; ytype Y;
	struct node {
		line v{}; node *le{}, *ri{};
		~node() { delete le; delete ri; }
	} *rt{};
	void clear() { delete rt; rt = nullptr; }
	int cmp(ytype x, ytype y) {
		if(x + eps < y) return 1; if(y + eps < x) return -1;
		return 0;
	}
	void upd(node *&nd, ll l, ll r, line u) {
		if(!nd) nd = new node();
		line &v = nd->v; ll mid = (l + r) >> 1;
		int b = cmp(v.at(mid), u.at(mid));
		if(b == 1 || (b == 0 && u < v)) swap(u, v);
		int bl = cmp(v.at(l), u.at(l)), br = cmp(v.at(r), u.at(r));
		if(bl == 1 || (bl == 0 && u < v)) upd(nd->le, l, mid, u);
		if(br == 1 || (br == 0 && u < v)) upd(nd->ri, mid+1, r, u);
	}
	void add(node *&nd, ll l, ll r, line u) {
		if(l >= L && r <= R) { upd(nd, l, r, u); return; }
		if(!nd) nd = new node(); ll mid = (l + r) >> 1;
		if(mid >= L) add(nd->le, l, mid, u);
		if(mid < R) add(nd->ri, mid + 1, r, u);
	}
	void add(line k, ll l = 1, ll r = n) {
		L = l; R = r; add(rt, 1, n, k);
	}
	void query(node *nd, ll l, ll r) {
		if(!nd) return; ytype yy = nd->v.at(P);
		if(yy >= Y - eps) {
			K = yy > Y + eps ? nd->v : min(K, nd->v); Y = yy;
		}
		if(l == r) return; ll mid = (l + r) >> 1;
		if(mid >= P) query(nd->le, l, mid);
		if(mid < P) query(nd->ri, mid + 1, r);
	}
	line query(ll p) {
		P = p; Y = YB; K = line(); query(rt, 1, n); return K;
	}
	void merge(node *&a, node *&b, ll l, ll r) {
		if(!b) return; if(!a) { a = b; b = 0; return; }
		if(l != r) {
			ll mid = (l + r) >> 1;
			merge(a->le, b->le, l, mid);
			merge(a->ri, b->ri, mid + 1, r);
		}
		upd(a, l, r, b->v); delete b;
	}
	void merge(lichao &b) { merge(rt, b.rt, 1, n); }
};
