//JP - Not in Kansas Anymore
#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

// Como foi especificado que era permitido,
// estou utilizando uma implementação de Segtree de outra pessoa.

// Implementação de uma Segtree Especial de Bruno Monteiro.
// Encontrada em: 
// https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/SegTree

// Copiada apenas a estrutura. O algoritmo é de minha autoria. 

struct Segtree {

	struct node {
		node *l, *r;
		int cnt;
		ll val, lazy;
		node() : l(NULL), r(NULL), cnt(0), val(0), lazy(0) {}
		void update() {
			cnt = 0, val = 0;
			for (auto i : {l, r}) if (i) {
				i->prop();
				cnt += i->cnt, val += i->val;
			}
		}
		void prop() {
			if (!lazy) return;
			val += lazy*(ll)cnt;
			for (auto i : {l, r}) if (i) i->lazy += lazy;
			lazy = 0;
		}
	};

	int n;
	vector<node*> seg;

	Segtree(vector<pair<int, int>>& v, int c) : n(v.size()), seg(c, NULL) {
		for (int i = 0; i < n; i++)
			seg[v[i].second] = insert(seg[v[i].second], i, v[i].first, 0, n-1);
	}

	~Segtree() {
		queue<node*> q;
		for (auto i : seg) q.push(i);
		while (q.size()) {
			auto i = q.front(); q.pop();
			if (!i) continue;
			q.push(i->l), q.push(i->r);
			delete i;
		}
	}

	node* insert(node* at, int idx, int val, int l, int r) {
		if (!at) at = new node();
		if (l == r) return at->cnt = 1, at->val = val, at;
		int m = (l+r)/2;
		if (idx <= m) at->l = insert(at->l, idx, val, l, m);
		else at->r = insert(at->r, idx, val, m+1, r);
		return at->update(), at;
	}
	
	ll query(node* at, int a, int b, int l, int r) {
		if (!at or b < l or r < a) return 0;
		at->prop();
		if (a <= l and r <= b) return at->val;
		int m = (l+r)/2;
		return query(at->l, a, b, l, m) + query(at->r, a, b, m+1, r);
	}
	
	ll query(int c, int a, int b) { return query(seg[c], a, b, 0, n-1); }
	
	void update(node* at, int a, int b, int x, int l, int r) {
		if (!at or b < l or r < a) return;
		at->prop();
		if (a <= l and r <= b) {
			at->lazy += x;
			return void(at->prop());
		}
		int m = (l+r)/2;
		update(at->l, a, b, x, l, m), update(at->r, a, b, x, m+1, r);
		at->update();
	}

	void update(int c, int a, int b, int x) { update(seg[c], a, b, x, 0, n-1); }
	
	void paint(node*& from, node*& to, int a, int b, int l, int r) {
		if (to == from or !from or b < l or r < a) return;
		from->prop();
		if (to) to->prop();
		if (a <= l and r <= b) {
			if (!to) {
				to = from;
				from = NULL;
				return;
			}
			int m = (l+r)/2;
			paint(from->l, to->l, a, b, l, m), paint(from->r, to->r, a, b, m+1, r);
			to->update();
			delete from;
			from = NULL;
			return;
		}
		if (!to) to = new node();
		int m = (l+r)/2;
		paint(from->l, to->l, a, b, l, m), paint(from->r, to->r, a, b, m+1, r);
		from->update(), to->update();
	}

	void paint(int c1, int c2, int a, int b) { paint(seg[c1], seg[c2], a, b, 0, n-1); }
};

int32_t main(){ _
	int n;
	while(cin >> n){
		vector<pair<int, int>> ini(n);
		int c13 = 1, c7 = 2;
		for(int i = 0; i < n; i++){
			cin >> ini[i].first;
			if(ini[i].first == 7)  ini[i].second = c7;
			else if(ini[i].first == 13) ini[i].second = c13;
			else ini[i].second = 0;
		}
		Segtree seg(ini, 3);
		
		int q; cin >> q;
		while(q--){
			int t; cin >> t;
			if(t == 1){
				int i, v; cin >> i >> v; i--;
				int cur, ccur, newc;
				
				// Change Value
				if(seg.query(c7, i, i) > 0) ccur = c7, cur = 7;
				else if(seg.query(c13, i, i) > 0) ccur = c13, cur = 13;
				else ccur = 0, cur = seg.query(0, i, i);
				seg.update(ccur, i, i, v - cur);

				// Change Color
				if(v == 13) newc = c13;
				else if(v == 7)  newc = c7;
				else newc = 0;
				seg.paint(ccur, newc, i, i);
			}

			else if(t == 2){
				int i, j, z, v; cin >> i >> j >> z >> v;
				i--, j--;
				int ccur = 0;
				if(v == 13) ccur = c13;
				if(v == 7) ccur = c7;

				if((z == 13)){
					seg.update(c13, i, j, v-13);
					seg.paint(c13, ccur, i, j);
				} else if((z == 7)){
					seg.update(c7, i, j, v-7);
					seg.paint(c7, ccur, i, j);
				}
			}

			else if(t == 3){
				int i, j; cin >> i >> j; i--, j--;
				cout << seg.query(0, i, j) + seg.query(c7, i, j) + seg.query(c13, i, j);
				cout << endl;
			}
		}
	}
	exit(0);
}
