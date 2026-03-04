/**
 * Author: Vannes
 * Date: 2025-10-27
 * License: CC0
 */
struct Node{ // key = index in (naive) array
	int prio=rand(), key, lzkey=0, sz=1;
	Node *lc=0, *rc=0;
	int val; // datas
};
int size(Node *node){
	if(!node) return 0; return node->sz;
}
void upd(Node *node,int x){ // update shift key values in
	if(!node) return;
	node->key += x;
	node->lzkey += x;
}
// split node into L<=x and x<R
pair<Node*,Node*> split(Node *node,int x){
	if(!node) return {0,0};
	if(node->lzkey){
		upd(node->lc, node->lzkey);
		upd(node->rc, node->lzkey);
		node->lzkey = 0;
	}
	if(node->key <= x){
		auto[l,r] = split(node->rc, x);
		node->rc = l;
		node->sz = size(node->lc) + size(node->rc) + 1;
		return {node, r};
	}
	else{
		auto[l,r] = split(node->lc, x);
		node->lc = r;
		node->sz = size(node->lc) + size(node->rc) + 1;
		return {l, node};
	}
}
Node* merge(Node *l, Node *r){
	if(!l) return r;
	if(!r) return l;
	for(auto node : {l,r}) if(node->lzkey){
		upd(node->lc, node->lzkey);
		upd(node->rc, node->lzkey);
		node->lzkey = 0;
	}

	if(l->prio > r->prio){
		l->rc = merge(l->rc, r);
		l->sz = size(l->lc) + size(l->rc) + 1;
		return l;
	}
	else{
		r->lc = merge(l, r->lc);
		r->sz = size(r->lc) + size(r->rc) + 1;
		return r;
	}
}
