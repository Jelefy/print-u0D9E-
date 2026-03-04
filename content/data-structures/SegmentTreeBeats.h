/**
 * Author: Jelefy
 * Date: 2025-10-31
 * License: CC0
 * Description: Support range chkmin \& add \& sum \& max \& history max.
 */
#pragma once

#define chkmax(x, y) (x) = max((x), (y))
int n, m, mx[N * 4], _mx[N * 4], smx[N * 4], cnt[N * 4];
int addmx[N * 4], _addmx[N * 4], addoth[N * 4], _addoth[N * 4];
long long sum[N * 4];
void pushup(int i) {
	sum[i] = sum[le] + sum[ri]; _mx[i] = max(_mx[le], _mx[ri]);
	if (mx[le] == mx[ri]) {
		mx[i] = mx[le]; smx[i] = max(smx[le], smx[ri]);
		cnt[i] = cnt[le] + cnt[ri];
	} else if (mx[le] > mx[ri]) {
		mx[i] = mx[le]; smx[i] = max(smx[le], mx[ri]);
		cnt[i] = cnt[le];
	} else {
		mx[i] = mx[ri]; smx[i] = max(smx[ri], mx[le]);
		cnt[i] = cnt[ri];
	}
}
void upd(int i, int l, int r,
	     int kmx, int _kmx, int koth, int _koth) {
	sum[i] += 1ll * kmx * cnt[i]
	          + 1ll * koth * (r - l + 1 - cnt[i]);
	chkmax(_mx[i], mx[i] + _kmx);
    chkmax(_addmx[i], addmx[i] + _kmx);
	mx[i] += kmx, addmx[i] += kmx;
	chkmax(_addoth[i], addoth[i] + _koth);
	addoth[i] += koth; if (smx[i] != -INF) smx[i] += koth;
}
void pushdown(int i, int l, int mid, int r) {
	int tmp = max(mx[le], mx[ri]);
	if (mx[le] == tmp) upd(le, l, mid,
		addmx[i], _addmx[i], addoth[i], _addoth[i]);
	else upd(le, l, mid,
		addoth[i], _addoth[i], addoth[i], _addoth[i]);
	if (mx[ri] == tmp) upd(ri, mid + 1, r,
		addmx[i], _addmx[i], addoth[i], _addoth[i]);
	else upd(ri, mid + 1, r,
		addoth[i], _addoth[i], addoth[i], _addoth[i]);
	addmx[i] = _addmx[i] = addoth[i] = _addoth[i] = 0;
}
void build(int i, int l, int r) {
	if (l == r) {
		rd(mx[i]); cnt[i] = 1; sum[i] = _mx[i] = mx[i];
		smx[i] = -INF; return;
	}
	int mid = (l + r) >> 1;
	build(le, l, mid); build(ri, mid + 1, r); pushup(i);
}
int L, R, K;
void add(int i, int l, int r) {
	if (l >= L && r <= R) { upd(i, l, r, K, K, K, K); return; }
	int mid = (l + r) >> 1; pushdown(i, l, mid, r);
	if (mid >= L) add(le, l, mid);
	if (mid < R) add(ri, mid + 1, r);
	pushup(i);
}
void tomin(int i, int l, int r) {
	if (K >= mx[i]) return;
	if (l >= L && r <= R && K > smx[i])
		return upd(i, l, r, K - mx[i], K - mx[i], 0, 0);
	int mid = (l + r) >> 1; pushdown(i, l, mid, r);
	if (mid >= L) tomin(le, l, mid);
	if (mid < R) tomin(ri, mid + 1, r);
	pushup(i);
}
long long getsum(int i, int l, int r) {
	if (l >= L && r <= R) return sum[i];
	int mid = (l + r) >> 1; pushdown(i, l, mid, r);
	long long ret = 0;
	if (mid >= L) ret += getsum(le, l, mid);
	if (mid < R) ret += getsum(ri, mid + 1, r);
	return ret;
}
int getmax(int i, int l, int r) { // current max
	if (l >= L && r <= R) return mx[i];
	int mid = (l + r) >> 1, ret = -INF; pushdown(i, l, mid, r);
	if (mid >= L) chkmax(ret, getmax(le, l, mid));
	if (mid < R) chkmax(ret, getmax(ri, mid + 1, r));
	return ret;
}
int _getmax(int i, int l, int r) { // history max
	if (l >= L && r <= R) return _mx[i];
	int mid = (l + r) >> 1, ret = -INF; pushdown(i, l, mid, r);
	if (mid >= L) chkmax(ret, _getmax(le, l, mid));
	if (mid < R) chkmax(ret, _getmax(ri, mid + 1, r));
	return ret;
}
