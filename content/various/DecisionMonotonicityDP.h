/**
 * Author: OI-Wiki
 * License: CC BY-SA 4.0 & SATA
 * Source: OI-Wiki
 * Description: Given $f[i] = \min_{lo(i) \le j \le hi(i)}w(j, i)$ where the (minimal)
 * optimal $j$ increases with $i$, computes $f[i]$ for $i = l\ldots r$. Entrance function: larsch (NOTE: restricted hi \& lo is not tested)
 * Time: O((N + (hi-lo)) \log N)
 * Status: tested on https://www.luogu.com.cn/problem/AT_abc355_g
 */
#pragma once

pair<val_t, int> f[N];
val_t w(int j, int i);
int lo(int ind) { return 1; }
int hi(int ind) {return ind; }
void upd(int i, int j) {f[i] = f(f[i], make_pair(w(j,i), j));}
void rec(int l, int r) {
	int mid = (l + r + 1) / 2;
	rep(j, max(f[l].second,lo(mid)), min(f[r].second,hi(mid))+1)
		upd(mid, j);
	if (mid < r) rec(l, mid);
	rep(j, max(l + 1, lo(r)), min(mid, hi(r)) + 1) upd(r, j);
	if (mid > l) rec(mid, r);
}
void larsch(int l, int r) {
	fill(f + l, f + r + 1, make_pair(INF, -1));
	upd(l, l), upd(r, l);
	rec(l, r);
}
