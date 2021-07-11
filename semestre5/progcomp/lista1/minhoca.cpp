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
const int MAX = 1e4 + 10;

int s, t, cycle; // Cycle index

vector<vector<ii>> g; // {Vertex, Weight}
vector<ii> p;
vector<ll> c; // -1 is White, -2 is Grey and -3 is Black
vector<ll> csize;
vector<ll> d;

void reset(){
	cycle = 0;
	g.assign(MAX, vector<ii>());
	c.assign(MAX, -1);
	csize.assign(MAX, -1);
	p.assign(MAX, {-1, 0});
}

void dfs(int x){
	c[x] = -2;
	for(auto ed: g[x]){
		int u = ed.f;
		int dis = ed.s;
		
		if(c[u] == -2 and p[x].f != u){ // Found cycle. Backtracking and counting size.
			int i = x;
			c[i] = cycle;
			while(i != u){
				dis += p[i].s;
				i    = p[i].f;
				c[i] = cycle;
			}
			csize[cycle] = dis;
			cycle++;

			continue;
		}

		if(c[u] == -1){
			p[u] = {x, dis};
			dfs(u);
		}
	}

	if(c[x] == -2) c[x] = -3;
}

void dijkstra(int x) {
	d = vector<ll> (s+10);
	for (int i=0; i < s+9; i++) d[i] = LINF;
	d[x] = 0;
	priority_queue<pair<ll,int>> pq;
	pq.push({0,x});

	while (pq.size()) {
		auto [ndist,u] = pq.top(); pq.pop();
		if (-ndist > d[u]) continue;

		for (auto [idx,w] : g[u]) if (d[idx] > d[u] + w) {
			d[idx] = d[u] + w;
			pq.push({-d[idx], idx});
		}
	}
}


int main(){ //_
	while(cin >> s >> t){
		reset();
		// Read
		while(t--){
			int a, b, w; cin >> a >> b >> w;
			a--, b--;
			g[a].pb({b,w}), g[b].pb({a,w});
		}

		// CalcCycle
		p[0] = {0, 0};
		dfs(0);

		// CalcQueries
		int	q; cin >> q;
		while(q--){
			int x, size; cin >> x >> size;
			x--, dijkstra(x);
			ll ans = LINF;
			for(int i = 0; i < s; i++)
				if(c[i] >= 0 and csize[c[i]] >= size)
					ans = min(ans, 2*d[i]+csize[c[i]]);
			cout << (ans == LINF ? -1 : ans) << endl;
		}
	}
	exit(0);
}
