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

// Dinic -- Código de Bernardo Amorim
// https://github.com/bernardoamorim/library/blob/master/code/graphs/dinic.cpp

struct Dinic {
	struct edge { 
		int to, id, cap; // id % 2 (0 if original, 1 if residual)
		edge (int to_, int id_, int cap_) : to(to_), id(id_), cap(cap_) {}
	};

	vector<vector<edge>> g;
	vector<int> flow, lvl, it;

	Dinic (int sz) : g(sz), lvl(sz), it(sz) {}

	void add_edge(int u, int v, int cap) {
		//cout << u << " " << v << " " << cap << endl;
		g[u].emplace_back(v, size(flow), cap), flow.push_back(0);
		g[v].emplace_back(u, size(flow), cap), flow.push_back(cap);
	}
	int dfs(int v, int flow_aug, int t) {
		if (v == t) return flow_aug;
		for (int& i = it[v]; i < size(g[v]); i++) {
			edge e = g[v][i];
			int left = e.cap - flow[e.id];
			if (lvl[e.to] == lvl[v] + 1 and left) {
				if (int aug = dfs(e.to, min(flow_aug, left), t)) {
					flow[e.id] += aug, flow[e.id^1] -= aug;
					return aug;
				}
			}
		}
		return 0;
	}
	bool bfs(int s, int t) {
		fill(begin(lvl), end(lvl), -1); 
		lvl[s] = 0;
		queue<int> q; 
		q.push(s);
		while (not empty(q)) {
			int u = q.front(); 
			q.pop();
			for (edge e : g[u]) if (e.cap - flow[e.id] > 0 and lvl[e.to] == -1)
				lvl[e.to] = lvl[u] + 1, q.push(e.to);
		}
		return lvl[t] != -1;
	}
	int max_flow(int s, int t) {
		int max_flow = 0;
		while (bfs(s, t)) {
			fill(begin(it), end(it), 0);
			while (int aug = dfs(s, INF, t)) max_flow += aug;
		}
		return max_flow;	
	}
	pair<int, vector<int>> min_cut(int s, int t) {
		int maxflow = max_flow(s, t);
		vector<int> part(size(g), 0), mincut;
		function<void(int)> find_aug = [&] (int u) {
			for (edge e : g[u])if (not part[e.to] and e.cap > flow[e.id])
				part[e.to] = 1, find_aug(e.to);
		};
		part[s] = 1, find_aug(s);
		for (int u = 0; u < size(g); u++) 
			for (edge e : g[u]) if (part[u] and not part[e.to] and not (e.id & 1)) 
				mincut.push_back(e.id / 2);
		return {maxflow, mincut};
	}
};

int n, m, a;

int solve(vector<tuple<int, int, int>> &edges, int mid){
	Dinic flow(n*mid+3);
	int sink = n*mid+2;
	
	//cout << "ADD WAITING" << endl;
	// Add waiting edges
	for(int i = 0; i < n; i++)
		for(int day = 1; day < mid; day++)
			flow.add_edge((day-1)*n + i, day*n + i, a);

	//cout << "ADD FLIGHTS" << endl;
	// Add flight edges
	for(auto [u, v, cap]: edges)
		for(int day = 1; day < mid; day++)
			flow.add_edge((day-1)*n + u, day*n + v, cap); 
	
	for(int day = 0; day < mid; day++)
		flow.add_edge(day*n + n - 1, sink, a);

	return flow.max_flow(0, sink);
}

int main(){ _
	while(1){
		cin >> n >> m >> a;
		if(n+m+a == 0) break;

		vector<tuple<int, int, int>> edges;
		while(m--){
			int u, v, cap; cin >> u >> v >> cap;
			u--, v--;
			edges.emplace_back(u, v, cap);
		}
		
		int l = 0, r = 1e2;
		while(l < r){
			int mid = (l+r)/2;
			if(solve(edges, mid) >= a) r = mid;
			else l = mid+1;
		}

		cout << l-1 << endl;
	}
	exit(0);
}
