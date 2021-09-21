//JP - Not in Kansas Anymore
#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back

// #define int ll
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll,ll> iill;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAX = 1e5 + 10;


struct Lazy{
	int sum;
	int ass;

	Lazy(){
		sum = 0;
		ass = -1;
	}
};


struct Node{
	int min;
	int idx;
	bool alive;

	Node(){
		min = INF;
		idx = 0;
		alive = false;
	}
};

namespace seg{
	int ROOT = 1;
	Node id; // Neutral element
	int sz;

	Node tree[4*MAX];
	Lazy lazy[4*MAX];

	// Operation
	Node op(Node a, Node b){
		Node c = Node();
		c.alive = (a.alive or b.alive);
		if(c.alive){
			if(a.min <= b.min) c = a;
			else c = b;
		}
		return c;
	}
	
	void push(int node){ // Propagates Lazyness to Children
		Lazy& l0 = lazy[node]; 
		Lazy& l1 = lazy[node*2];
		Lazy& l2 = lazy[node*2+1];
		Node& t1 = tree[node*2]; 
		Node& t2 = tree[node*2+1];
		
		if(l0.ass != -1){
			if(t1.alive and t1.min != INF) t1.min = l0.ass + l0.sum;
			if(t2.alive and t2.min != INF) t2.min = l0.ass + l0.sum;
			if(l0.ass == INF){
				t1.alive = false;
				t2.alive = false;
			}
			l1 = l0, l2 = l0;	
		} else{
			if(t1.alive and t1.min != INF) t1.min += l0.sum;
			if(t2.alive and t2.min != INF) t2.min += l0.sum;
			l1.sum += l0.sum;
			l2.sum += l0.sum;
		}

		l0.ass = -1;
		l0.sum = 0;
	}

	void build(int n, int k){
		while(__builtin_popcount(n) != 1) n++;
		sz = n;

		for(int i = 0; i < sz; i++)
			tree[i] = Node(), lazy[i] = Lazy();
		
		for(int i = 0; i < sz; i++){
			tree[sz + i].alive = true;
			tree[sz + i].min   = k;
			tree[sz + i].idx   = i;
		} // Leaves

		for(int i = sz-1; i >= ROOT; i--)
			tree[i] = op(tree[2*i], tree[2*i+1]); // Segments
	}

	void update(int node, int n_low, int n_high, int q_low, int q_high, int type,
	int v){
		if(n_low >= q_low and n_high <= q_high){
			if(tree[node].alive){
				if(type == 0){ // Assign
					tree[node].min = v;
					if(v == INF) tree[node].alive = false;
				}
				else tree[node].min += v;
			}

			if(type == 0){
				lazy[node].ass = v;
				lazy[node].sum = 0;
			}
			else lazy[node].sum += v;

			return;
		} else if(n_high < q_low or  n_low  >  q_high) return; // Not modified
		
		push(node);
		int mid  = (n_low + n_high)/2; // Mid Point of Interval
		update(node*2,   n_low, mid,    q_low, q_high, type, v);
		update(node*2+1, mid+1, n_high, q_low, q_high, type, v);

		tree[node] = op(tree[2*node], tree[2*node+1]); // Join halves
	}


	Node query(int node, int n_low, int n_high, int q_low, int q_high){		
		if(n_low >= q_low and n_high <= q_high) return tree[node]; // Inside
		if(n_high < q_low or  n_low  >  q_high) return id; // Neutral Element
		
		push(node);
		int mid  = (n_low + n_high)/2; // Mid Point of Interval
		Node left  = query(node*2,   n_low, mid,    q_low, q_high);
		Node right = query(node*2+1, mid+1, n_high, q_low, q_high);

		return op(left, right);
	}

	// Friendly
	void update(int low, int high, int type, int v){
		update(ROOT, 0, sz-1, low, high, type, v);
	}
	
	Node query(int low, int high){return query(ROOT, 0, sz-1, low, high);}
};

int32_t main(){ _
	// Type 0 is Assign | Type 1 is Sum
	int n, q, k; 
	while(cin >> n >> q >> k){
		seg::build(n, k);
		for(int qq = 1; qq <= q; qq++){
			int l, r; cin >> l >> r; l--, r--;
			seg::update(l, r, 0, k+1); // Põe Aguinha
			seg::update(0, n-1, 1, -1); // Sofre

			// Agora vamos matar
			Node Q = seg::query(0, n);
			while(Q.min == 0){
				seg::update(Q.idx, Q.idx, 0, INF);
				Q = seg::query(0, n);
			}
		}
	
		vector<int> ans;
		for(int i = 0; i < n; i++){
			Node Q = seg::query(i, i);
			if(Q.alive) ans.pb(i+1);
		}
		cout << ans.size();
		for(int i: ans) cout << " " << i;
		cout << endl;
	}
	exit(0);
}
