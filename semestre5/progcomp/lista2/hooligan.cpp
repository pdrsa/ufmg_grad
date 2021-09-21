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

int main(){ _
	while(1){
		int n, m, k; cin >> n >> m >> k;
		if(n + m + k == 0) break;

		vector<vector<int>> g(n, vector<int> (n, m));
		vector<int> p(n);
		while(k--){
			int a, b; char c;
			cin >> a >> c >> b;
			if(c == '=') p[a]++, p[b]++;
			else if(c == '<') p[b] += 2;
			else p[a] += 2;

			g[a][b]--, g[b][a]--;
		}

		// Max I can get
		for(int i = 1; i < n; i++) p[0] += 2 * g[0][i];
		// Calculating number of V
		int nG = 0;
		for(int i = 1; i < n; i++) for(int j = i+1; j < n; j++) nG++;
		
		Dinic flow(nG + n + 1);
		// Source = 0
		// Sink   = n

		int fNec = 0;
		int idx = n+1;
		for(int i = 1; i < n; i++){
			for(int j = i+1; j < n; j++){
				flow.add_edge(0,   idx, g[i][j] * 2);
				flow.add_edge(idx, i,   g[i][j] * 2);
				flow.add_edge(idx, j,   g[i][j] * 2);
				
				fNec += g[i][j] * 2;
				idx++;
			}

			int cap = p[0]-p[i]-1;
			if(cap) flow.add_edge(i, n, cap);
		}
		
		bool ans = true;
		if(fNec == 0) for(int i = 1; i < n; i++) ans = ans and (p[0] > p[i]);
		else ans = flow.max_flow(0, n) >= fNec;
		
		cout << (ans ? "Y" : "N") << endl;
	}
	exit(0);
}
