/**
 * Author: Vannes
 * Date: 2025-10-27
 * License: CC0
 */

struct Line { // mincht
	Int m, c;
	Int eval(Int x) { return m * x + c; }
	Int cut(Line l) { return (c - l.c) / (l.m - m); }
};
struct Cht {
	Line s[N]; // note here is a constant N
	int st = 1, ed = 0;
	void upd(Line cur) {
		while (st<ed && cur.cut(s[ed])<=s[ed].cut(s[ed-1])) --ed;
		s[++ed] = cur;
	}
	Line qry(Int x) {
		while (st < ed && s[st].eval(x) > s[st+1].eval(x)) st++;
		return s[st];
	}
};
