/**
 * Author: Jelefy
 * Date: 2025-10-30
 * License: CC0
 * Description: Dynamic tree supporting path add \& sum.
 * Usage: For path lazy mod/query, split(x, y) and mod/read nd[y];
 *        For vertex mod, split(x, x), mod nd[x], and pushup(x).
 *        Note that you need to consider null nodes.
 */

#pragma once

struct node { // default constructor for null node
	unsigned val{}, sum{}, add{}, sz{}; node() = default;
	node(unsigned val) : val(val), sum(val), sz(1u) {}
	void pushup(node &lc, node &rc) {
		sz = (lc.sz + rc.sz + 1u) % mod;
		sum = (lc.sum + rc.sum + val) % mod;
	}
	void upd(unsigned v) {
		sum = (sum + sz * v) % mod;
		val = (val + v) % mod; add = (add + v) % mod;
	}
	void pushdown(node &lc, node &rc) {
		if (add == 0) return;
		if (lc.sz) lc.upd(add); if (rc.sz) rc.upd(add); add = 0;
	} // lc/rc.sz == 0 implies null node
} nd[N];

int ch[N][2], fa[N], st[N]; bool rev[N];
bool isrt(int i) { return ch[fa[i]][0]!=i && ch[fa[i]][1]!=i; }
void pushup(int i) { nd[i].pushup(nd[ch[i][0]],nd[ch[i][1]]); }
void pushdown(int i) {
	nd[i].pushdown(nd[ch[i][0]], nd[ch[i][1]]);
	if (!rev[i]) return; else swap(ch[i][0], ch[i][1]);
	rev[ch[i][0]] ^= 1; rev[ch[i][1]] ^= 1; rev[i] = 0;
}
bool chk(int i) { return ch[fa[i]][1] == i; }
void rot(int x) {
	int y = fa[x], k = chk(x);
	if (!isrt(y)) ch[fa[y]][chk(y)] = x;
	fa[x] = fa[y]; ch[y][k] = ch[x][!k]; fa[ch[y][k]] = y;
	ch[x][!k] = y; fa[y] = x; pushup(y);
}
void splay(int i, int top = 0) {
	for (int j = i; st[top++] = j, !isrt(j); j = fa[j]);
	do pushdown(st[--top]); while(top);
	for (int j = fa[i]; !isrt(i); rot(i), j = fa[i])
		if (!isrt(j)) rot(chk(i) == chk(j) ? j : i);
	pushup(i);
}
void access(int i) {
	for (int j = 0; i; j = i, i = fa[j])
		splay(i), ch[i][1] = j, pushup(i);
}
void makert(int i) { access(i); splay(i); rev[i] ^= 1; }
int findrt(int i) {
	access(i); splay(i); while (ch[i][0]) i = ch[i][0];
	splay(i); return i;
}
void split(int x, int y) { makert(x); access(y); splay(y); }
bool link(int x, int y) {
	makert(x); if (findrt(y) == x) return false;
	fa[x] = y; return true;
}
bool connected(int x, int y) { return findrt(x) == findrt(y); }
bool hasedge(int x, int y) {
	if (!connected(x, y)) return false;
	split(x, y); return ch[y][0] == x && !ch[x][1];
}
bool cut(int x, int y) {
	if (!hasedge(x, y)) return false;
	ch[y][0] = 0; fa[x] = 0; return true;
}
