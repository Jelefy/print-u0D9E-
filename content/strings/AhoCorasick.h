/**
 * Author: Jelefy
 * Date: 2025-10-30
 * License: CC0
 * Description: Aho-Corasick automaton for multiple pattern matching.
 */
#pragma once

const int M = 26;   // alphabet size
const char A = 'a'; // first char in alphabet
int ch[N][M], cnt[N], fail[N], id; int q[N], l, r;
void insert(const char *s) {
	int p = 0;
	for (char *c = s; *c; c++)
		p = ch[p][*c - A] ? ch[p][*c - A] : ch[p][*c - A] = ++id;
	cnt[p]++;
}
void init() {
	for (int i = 0; i < M; i++) if (ch[0][i]) q[r++] = ch[0][i];
	while (l != r) {
		int p = q[l++];
		for (int i = 0; i < M; i++) {
			if (ch[p][i])
				fail[ch[p][i]] = ch[fail[p]][i], q[r++] = ch[p][i];
			else ch[p][i] = ch[fail[p]][i];
		}
	}
}
