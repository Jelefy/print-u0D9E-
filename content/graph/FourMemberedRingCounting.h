/**
 * Author: Jelefy
 * Date: 2025-10-30
 * License: CC0
 * Time: O(E \sqrt E)
 */
#pragma once

long long count_4(int n, vector<pii> &edges) {
	rep(i, 0, n) g[i].clear(), rg[i].clear();
	fill(deg, deg + n, 0); long long ans = 0;
	for (auto [u, v] : edges) deg[u]++, deg[v]++;
	for (auto [u, v] : edges) {
		if (pii(deg[u], u) > pii(deg[v], v)) swap(u, v);
		g[u].push_back(v); rg[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		long long B1 = 0, B2 = 0, B3 = 0;
		for (int j : g[i]) for (int k : g[j])
			if (k != i) B1 += cnt1[k], cnt1[k]++;
		for (int j : rg[i]) for (int k : g[j]) if (k != i)
			B2 += cnt1[k], B3 += cnt2[k], cnt2[k]++;
		for (int j : g[i]) for (int k : g[j]) cnt1[k] = 0;
		for (int j : rg[i]) for (int k : g[j]) cnt2[k] = 0;
		ans += 2 * B1 + 2 * B2 + B3;
	}
	return ans / 2;
}
