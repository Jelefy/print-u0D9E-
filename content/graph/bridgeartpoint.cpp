/**
 * Author: Vannes
 * Date: 2020-01-01
 * License: CC0
 * Source: https://bs.com
 * Description: Empty
 */

const int N = 1e5+5;

int n, m;
V<int> adj[N];

// discovery time
int tin[N];
int timer = 0;

// low-link value
// the smallest (earliest time) tin[] value that you
// can get without using the direct edge to parent
int low[N];

void dfs(int x, int par){
	tin[x] = low[x] = ++timer;
	for(int y : adj[x]) if(y != par){
		// undiscovered yet
		if(tin[y] == 0){
			dfs(y, x);
		}
		low[x] = min(low[x], low[y]);

		// if xy is a bride
		if(low[y] > tin[x]){
			// ...
		}
		// if x is art point
		if(low[y] >= tin[x]){
			// ...
		}
	}
	// special case : root is art point if
	// it has >= 2 child in dfs-tree
}
