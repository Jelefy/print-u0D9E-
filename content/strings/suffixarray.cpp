/**
 * Author: Vannes
 * Date: 2020-01-01
 * License: CC0
 * Source: https://bs.com
 * Description: suffix array 
 */
V<int> sort_cyclic_shifts(string const& s) {
	int n = s.size(); const int alphabet = 256;
	V<int> p(n), c(n), cnt(max(alphabet, n), 0);
	rep(i,0,n) cnt[s[i]]++;
	rep(i,1,alphabet) cnt[i]+=cnt[i-1];
	rep(i,0,n) p[--cnt[s[i]]] = i;
	c[p[0]] = 0; int classes = 1;
	rep(i,1,n){
		if(s[p[i]]!=s[p[i-1]]) classes++;
		c[p[i]] = classes - 1;
	} V<int> pn(n), cn(n);
	for(int h=0; (1LL<<h)<n; h++){
		rep(i,0,n){
			pn[i] = p[i] - (1LL<<h);
			if(pn[i]<0) pn[i] += n;
		}
		fill(cnt.begin(), cnt.begin() + classes, 0);
		rep(i,0,n) cnt[c[pn[i]]]++;
		rep(i,1,classes) cnt[i] += cnt[i-1];
		for(int i=n-1; i>=0; i--) p[--cnt[c[pn[i]]]] = pn[i];
		cn[p[0]] = 0; classes = 1;
		rep(i,1,n){
			pii cur = {c[p[i]], c[(p[i]+(1<<h))%n]};
			pii prev = {c[p[i-1]], c[(p[i-1]+(1<<h))%n]};
			if(cur!=prev) ++classes;
			cn[p[i]] = classes - 1;
		} c.swap(cn);
	} return p;
}
V<int> suffix_array_construction(string s) {
	s += "$"; V<int> sorted_shifts = sort_cyclic_shifts(s);
	sorted_shifts.erase(sorted_shifts.begin()); return sorted_shifts;
}
V<int> lcp_construction(string const& s,V<int> const& p) {
	int n = s.size(); V<int> rank(n, 0);
	rep(i,0,n) rank[p[i]] = i;
	int k = 0; V<int> lcp(n-1, 0);
	rep(i,0,n){
		if(rank[i]==n-1){ k = 0; continue; }
		int j = p[rank[i]+1];
		while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
		lcp[rank[i]] = k;
		if(k) k--;
	}
	return lcp;
}
