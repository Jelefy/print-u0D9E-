/**
 * Author: Jelefy
 * Date: 2025-10-31
 * License: CC0
 * Description: Mergeable min heap. find(x) finds the root of the heap to which x belongs. The operands of merge() and pop() must all be roots.
 */
#pragma once

const int N = 1e5 + 1; int idx = 1;
struct leftist { int val, fa, ls, rs, d; } heap[N];
int create(int val) { heap[idx] = {val, idx}; return idx++; }
int merge(int x, int y) {
	if (!x || !y) return x | y;
	if (heap[x].val > heap[y].val) swap(x, y);
	heap[y].fa = x; heap[x].rs = merge(heap[x].rs, y);
	if (heap[heap[x].ls].d < heap[heap[x].rs].d)
		swap(heap[x].ls, heap[x].rs);
	heap[x].d = heap[heap[x].rs].d + 1; return x;
}
void pop(int x) {
	int rt = merge(heap[x].ls, heap[x].rs);
	heap[rt].fa = rt; heap[x].fa = rt;
}
int find(int x) {
	return x == heap[x].fa ? x : heap[x].fa = find(heap[x].fa);
}
