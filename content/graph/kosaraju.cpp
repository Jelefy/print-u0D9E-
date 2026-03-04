/**
 * Author: Vannes
 * Date: 2025-10-27
 * License: CC0
 * Description: Kosaraju algorithm for SCC
 */
vi adj[N], radj[N], by_tout; bool vis[N]; int id[N];
void make_edge(int x, int y) { adj[x].pb(y); radj[y].pb(x); }
void dfs0(int x) { // sort nodes by out time
	if (vis[x]) return;
	vis[x] = true; for (int y : adj[x]) dfs0(y);
	by_tout.pb(x);
}
void dfs1(int x, int compid) { // assign component id to nodes
	id[x] = compid;
	for (int y : radj[x]) if (id[y] == 0) dfs1(y, compid);
}
int kosaraju(int n) {
	rep(i, 1, n + 1) if (!vis[i]) dfs0(i);
	reverse(all(by_tout)); int compid = 0;
	for (int i : by_tout) if (id[i] == 0) dfs1(i, ++compid);
	return compid;
}
