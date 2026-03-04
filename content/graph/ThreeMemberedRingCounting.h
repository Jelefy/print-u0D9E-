/**
 * Author: Jelefy
 * Date: 2025-10-30
 * License: CC0
 * Time: O(E \sqrt E)
 */
#pragma once

int count_3(int n, vector<pii> &edges) {
	fill(deg, deg + n, 0); fill(tim, tim + n, -1);
	rep(i, 0, n) g[i].clear(); int ans = 0;
	for (auto [u, v] : edges) deg[u]++, deg[v]++;
	for (auto [u, v] : edges) {
		if (pii(deg[u], u) > pii(deg[v], v)) swap(u, v);
		g[u].push_back(v);
	}
	for (int i = 0; i < n; i++) {
		for (int j : g[i]) tim[j] = i;
		for (int j : g[i]) for (int k : g[j]) ans += tim[k] == i;
	}
	return ans;
}
