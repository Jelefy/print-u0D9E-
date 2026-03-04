/**
 * Author: Vannes
 * Date: 2020-01-01
 * License: CC0
 * Source: https://bs.com
 * Description: MaxFlow Dinic algorithm with scaling. O(N * M * log(capacity))
 */
const int INF = 1e18;


int n, m; // nodes and edges
V<V<int>> adj; // adj[i] = {list of edges ids ...}
V<array<int,4>> edgs; // {u, v, flowing, max_capacity}
int s, t, lim; // source nodes, sink nodes, limit of new flow

// make edge from a to b with capacity c
void make_edge(int a,int b,int c){                                                                           
	// edgs[id] : direct edge. edgs[id^1] : back edge
	adj[a].push_back(edgs.size());
	edgs.push_back({a,b,0,c});
	adj[b].push_back(edgs.size());
	edgs.push_back({b,a,c,c});
}

// assign depth (=distance from source) to nodes
V<int> d;
bool bfs(){
	d = V<int>(n+1,INF); d[s] = 0;
	queue<int> que; que.push(s);
	while(!que.empty() && d[t]==INF){
		int x = que.front(); que.pop();
		for(int id : adj[x]){
			auto&[from,to,f,c] = edgs[id];
			if(d[to]==INF && c-f>=lim){
				d[to] = d[x]+1; que.push(to);
			}
		}
	}
	return d[t]!=INF;
}

V<int> pt; // pointer to the current unfinished edge
bool dfs(int v){ // try adding flow
	if(v==t) return 1; // sink is reached
	for(; pt[v]<(int)adj[v].size(); pt[v]++){
		auto&[from,to,f,c] = edgs[adj[v][pt[v]]];
		if(d[to]==d[v]+1 && c-f>=lim && dfs(to)){
			f += lim; // direct edge
			edgs[adj[v][pt[v]]^1][2] -= lim; // back edge
			return 1; // path is found, flow is added
		}
	}
	return 0; // path isn't found, no flow is added
}

int dinic(){ // runner code
	int ret = 0;
	for(lim=(1LL<<60); lim;){ // with scaling
		if(!bfs()){ // check if sink is reachable
			lim >>= 1; continue;
		}
		pt = V<int>(n+1); // reset pointers
		while(dfs(s)) ret+=lim; // repeatedly add flow
	}
	return ret;
}
