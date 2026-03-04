/**
 * Author: Jelefy
 * Date: 2026-01-31
 * License: CC0
 * Description: After building the graph \texttt{g}, call \texttt{cdinit} (which returns the number of layers). Everything is $1$-indexed.\\
 * \texttt{cen[l][u]}: The root of $u$ at layer $l$ ($0$ if none).\\
 * \texttt{dist[l][u]}: The dist to the root of $u$ at layer $l$.
 */
#pragma once

vector<vi> g, cen, dist;
int getcen(int u, int f, int s, int l) {
	bool iscen = true; int sz = 1;
	for (int v : g[u]) {
		if (v == f || cen[l - 1][v] != cen[l - 1][u]) continue;
		int ret = getcen(v, u, s, l); if (ret > 0) return ret;
		sz -= ret; if (-ret > s / 2) iscen = false;
	}
	if (s - sz > s / 2) iscen = false;
	return iscen ? u : -sz;
}
int setcen(int u, int f, int c, int l) {
	int s = 1; cen[l][u] = c; dist[l][u] = dist[l][f] + 1;
	for (int v : g[u])
		if (v != f && v != cen[l - 1][u] && cen[l - 1][v] == cen[l - 1][u]) s += setcen(v, u, c, l);
	return s;
}
int decompose(int u, int s, int l) {
	int m = l, c = getcen(u, cen[l - 1][u], s, l); cen[l][c] = c;
	for (int v : g[c])
		if (v != cen[l - 1][c] && cen[l - 1][v] == cen[l - 1][c])
			m = max(m, decompose(v, setcen(v, c, c, l), l + 1));
    return m;
}
int cdinit(int n) {
	int m = bit_width<unsigned>(n);
	cen = vector<vi>(m + 1, vi(n + 1));
	dist = vector<vi>(m + 1, vi(n + 1));
	return decompose(1, n, 1);
}
