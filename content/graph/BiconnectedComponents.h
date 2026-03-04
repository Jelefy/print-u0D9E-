/**
 * Author: Simon Lindholm and Jelefy
 * Date: 2025-10-30
 * License: CC0
 * Source: folklore and Jelefy
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are x least two distinct paths between any two nodes. Note that a node can
 *  be in several components. An edge which is not in a component is a bridge.
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *	ed[a].emplace_back(b, eid);
 *	ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& vlist, const vi\& elist) {...});
 * Time: O(E + V)
 * Status: orginal version before Jelefy tested during MIPT ICPC Workshop 2017
 */
#pragma once

vi tin, ste, stv; vector<vector<pii>> ed; int rt, Time;
template<class F>
int tarjan(int x, int par, F& f) {
	if (ed[x].empty()) { /* iso point */ return -1; }
	int me = tin[x] = ++Time, top = me, cnt = 0;
	bool canart = x != rt; stv.push_back(x);
	for (auto [y, e] : ed[x]) if (e != par) {
		if (tin[y]) {
			top = min(top, tin[y]);
			if (tin[y] < me) ste.push_back(e);
		} else {
			cnt++; int svi = sz(stv), sei = sz(ste);
			int up = tarjan(y, e, f); top = min(top, up);
			if (up < me) ste.push_back(e);
			else {
				if (canart) { canart = false; /* x is an art point */ }
				if (up == me) {
					stv.push_back(x), ste.push_back(e);
					f(vi(stv.begin() + svi, stv.end()),
					  vi(ste.begin() + sei, ste.end()));
					ste.resize(sei);
				} else { /* e is a bridge */ }
				stv.resize(svi);
			}
		}
	}
	if (x == rt) stv.clear();
	if (x == rt && cnt > 1) { /* x is an art point */ }
	return top;
}

template<class F>
void bicomps(F f) {
	tin.assign(sz(ed), 0); Time = 0;
	rep(i, 0, sz(ed)) if (!tin[i]) { rt = i; tarjan(i, -1, f); }
}
