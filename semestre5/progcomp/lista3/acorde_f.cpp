//JP - Not in Kansas Anymore
#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll,ll> iill;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

// JP - Not in Kansas Anymore

// Segtree with Lazy Propagation

// Build  - O(n)
// Update - O(log n) <-- Update on range _ Update is operation
// Query  - O(log n)

struct Segtree{
	int ROOT = 1;
	vector<int> id = vector<int>(9); // Neutral element
	int sz;

	vector<vector<int>> tree;
	vector<int> lazy;
	
	// Operation
	vector<int> op(vector<int> a, vector<int> b){
		vector<int> c(9);
		for(int i = 0; i < 9; i++) c[i] = a[i] + b[i];

		return c;
	};
	// (Update operation is set to sum, change it in code if needed)
	vector<int> shift(vector<int> &v, int x){
		vector<int> u(9);
		for(int i = 0; i < 9; i++)
			u[(i+x) % 9] = v[i];
		return u;
	}

	void push(int node){ // Propagates Lazyness to Children
		tree[node*2]   = shift(tree[node*2], lazy[node]);
		tree[node*2+1] = shift(tree[node*2+1], lazy[node]);
		lazy[node*2]   = (lazy[node*2] + lazy[node]) % 9;
		lazy[node*2+1] = (lazy[node*2+1] +  lazy[node]) % 9;
		lazy[node]     = 0;
	}

	void build(int n){
		sz = n;
		while(__builtin_popcount(sz) != 1) sz++;

		tree.resize(2 * sz);
		lazy.resize(2 * sz);
		for(int i = 0; i < sz; i++){
			vector<int> oneHot(9, 0);
			oneHot[1] = 1;
			tree[sz + i] = oneHot; // Leaves
		}

		for(int i = sz-1; i >= ROOT; i--)
			tree[i] = op(tree[2*i], tree[2*i+1]); // Segments
	}

	void update(int node, int n_low, int n_high, int q_low, int q_high, int v){		
		if(n_low >= q_low and n_high <= q_high){
			tree[node] = shift(tree[node], v);
			lazy[node] += v;
			return;
		} else if(n_high < q_low or  n_low  >  q_high) return; // Not modified
		
		push(node);
		int mid  = (n_low + n_high)/2; // MId Point of Interval
		update(node*2,   n_low, mid,    q_low, q_high, v);
		update(node*2+1, mid+1, n_high, q_low, q_high, v);

		tree[node] = op(tree[2*node], tree[2*node+1]); // Join halves
	}


	vector<int> query(int node, int n_low, int n_high, int q_low, int q_high){		
		if(n_low >= q_low and n_high <= q_high) return tree[node]; // Inside
		if(n_high < q_low or  n_low  >  q_high) return id; // Neutral Element
		
		push(node);
		int mid  = (n_low + n_high)/2; // Mid Point of Interval
		return op(query(node*2,   n_low, mid,    q_low, q_high),
			      query(node*2+1, mid+1, n_high, q_low, q_high)); // Join halves
	}

	// Friendly
	void update(int low, int high, int v){update(ROOT, 0, sz-1, low, high, v);}
	vector<int> query(int low, int high){return query(ROOT, 0, sz-1, low, high);}
};


int32_t main(){ _
	int n, q; cin >> n >> q;
	Segtree seg; seg.build(n);
	while(q--){
		int a, b; cin >> a >> b;
		vector<int> ans = seg.query(a, b);
		int f = 0, maxi = ans[0];
		for(int i = 1; i < 9; i++) if(ans[i] >= maxi) f = i, maxi = ans[i];
		seg.update(a, b, f);
	}

	for(int i = 0; i < n; i++){
		vector<int> ans = seg.query(i, i);
		for(int j = 0; j < 9; j++){
			if(ans[j]){
				cout << j << endl;
				break;
			}
		}
	}
	exit(0);
}
