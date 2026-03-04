/**
 * Author: Vannes
 * Date: 2025-10-27
 * License: CC0
 * Description: Maintain changing point of slopes of an (virtual) array a[]
 */
struct Slopes {
	int base = 0; // minimum value
	multiset<int> neg, pos; // neg=left border, pos=right border
	int lzneg = 0, lzpos = 0;
	void insert_neg(int x) { neg.insert(x - lzneg); }
	void insert_pos(int x) { pos.insert((x - lzpos)); }
	int base_neg() { return *prev(neg.end()) + lzneg; }
	int base_pos() { return *pos.begin() + lzpos; }
	void make_prfmin() { pos.clear(); } // into prefix/suffix min
	void make_sufmin() { neg.clear(); }
	// into min of surroundings a[i] := min(a[i-l]...a[i+r])
	void make_rangemin(int l, int r) { lzneg -= r; lzpos += l; }
	// increase slope in prefix/suffix
	void add_suf(int i) { // add a[i]+=0, a[i+1]+=1, a[i+2]+=2...
		if (neg.empty() || base_neg() <= i) insert_pos(i);
		else {
			base += abs(base_neg() - i);
			insert_pos(base_neg()); neg.erase(prev(neg.end()));
			insert_neg(i);
		}
	}
	void add_prf(int i) { // add a[i]+=0, a[i-1]+=1, a[i-2]+=2...
		if (pos.empty() || i <= base_pos()) insert_neg(i);
		else {
			base += abs(base_pos() - i);
			insert_neg(base_pos()); pos.erase(pos.begin());
			insert_pos(i);
		}
	}
};
