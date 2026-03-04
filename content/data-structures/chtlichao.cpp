/**
 * Author: Vannes
 * Date: 2025-10-27
 * License: CC0
 * Description: Max Lichao Tree. To change to min cht, set value of MINCHT
 */

// .upd(m,c) = insert line m*x+c
// .qry(x) = get minimum a*x+b
const int L = -1e9 - 5, R = 1e9 + 5;
#define mid ((tl + tr) >> 1)
struct Cht {
	static const bool MINCHT = 0;
	// evaluate y=p*x+q at x=b
	inline int eval(pii a, int b) { return a.ff * b + a.ss; }
	V<pii> st = {{0, -INF}};
	V<int> lc = {-1}, rc = {-1};
	int make() {
		st.push_back({0, -INF});
		lc.push_back(-1), rc.push_back(-1);
		return st.size() - 1;
	}
	void _upd(pii a, int v = 0, int tl = L, int tr = R) {
		if (eval(a, mid) > eval(st[v], mid)) swap(a, st[v]);
		if (eval(a, tl) > eval(st[v], tl)) {
			if (lc[v] == -1) lc[v] = make(), st[lc[v]] = st[v];
			_upd(a, lc[v], tl, mid);
		}
		if (eval(a, tr) > eval(st[v], tr)) {
			if (rc[v] == -1) rc[v] = make(), st[rc[v]] = st[v];
			_upd(a, rc[v], mid + 1, tr);
		}
	}
	void upd(pii a) { MINCHT ? _upd({-a.ff, -a.ss}) : _upd(a); }
	void upd(int m, int c) { upd({m, c}); }

	int _qry(int x, int v = 0, int tl = L, int tr = R) {
		if (v == -1) return -INF;
		if (tl == tr) return eval(st[v], x);
		if (x <= mid) return max(eval(st[v], x),
		                         _qry(x, lc[v], tl, mid));
		else return max(eval(st[v], x),
		                _qry(x, rc[v], mid + 1, tr));
	}
	int qry(int x) { return MINCHT ? -_qry(x) : _qry(x); }
};
#undef mid
