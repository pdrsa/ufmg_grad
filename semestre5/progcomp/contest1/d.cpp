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

struct Dinic {
	struct edge { 
		int to, id;
		double cap; // id % 2 (0 if original, 1 if residual)
		edge (int to_, int id_, double cap_) : to(to_), id(id_), cap(cap_) {}
	};

	vector<vector<edge>> g;
	vector<double> flow, lvl;
	vector<int> it;
	
	Dinic (int sz) : g(sz), lvl(sz), it(sz) {}
	
	void add_edge(int u, int v, double cap) {
		g[u].emplace_back(v, (double) flow.size(), cap); 
		flow.push_back(0);
		g[v].emplace_back(u, (double) flow.size(), cap); 
		flow.push_back(cap);
	}

	double dfs(int v, double flow_aug, int t) {
		if (v == t)
			return flow_aug;
		for (int& i = it[v]; i < g[v].size(); i++) {
			edge e = g[v][i];
			double left = e.cap - flow[e.id];
			if (lvl[e.to] == lvl[v] + 1 and left) {
				double aug = dfs(e.to, min(flow_aug, left), t);
				if (aug) {
					flow[e.id] += aug, flow[e.id^1] -= aug;
					return aug;
				}
			}
		}
		return 0;
	}
	bool bfs(int s, int t) {
		fill(lvl.begin(), lvl.end(), -1); 
		lvl[s] = 0;
		queue<int> q; 
		q.push(s);
		while (not q.empty()) {
			int u = q.front(); 
			q.pop();
			for (edge e : g[u])
				if (e.cap - flow[e.id] > 0 and lvl[e.to] == -1)
					lvl[e.to] = lvl[u] + 1, q.push(e.to);
		}
		return lvl[t] != -1;
	}

	double max_flow(int s, int t) {
		double max_flow = 0;
		while (bfs(s, t)) {
			fill(it.begin(), it.end(), 0);
			while (double aug = dfs(s, INF, t)) 
				max_flow += aug;
		}
		return max_flow;	
	}

};


vector<tuple<int, int, int>> ed;

int n, x;

//const ll MU = 1e6;

bool solve(double m){
	Dinic flow(n);

	for(auto [a, b, w]: ed)
		flow.add_edge(a, b, double(w)/m);

	return (flow.max_flow(0, n-1) - double(x) >= 1e-6);
}

int main(){ //_
	int m; cin >> n >> m >> x;
	for(int i = 0; i < m; i++){
		ll a, b, w; cin >> a >> b >> w;
		a--, b--;
		ed.emplace_back(a, b, w);
	}

	double ini = 0, fim = 100000;
	while(fim - ini >= (1e-6)){
		double mid = (ini + fim)/double(2);
		if(solve(mid)) ini = mid;
		else fim = mid;
	}
	cout << ini * x << endl;
	exit(0);
}
