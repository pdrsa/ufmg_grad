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

vector<vector<ii>> g;
vector<ll> d;

int n, m;

void dijkstra(int x){
	d = vector<ll> (n, LINF);
	d[x] = 0;

	priority_queue<pair<ll, int>> q;
	q.push({0, x});

	while(!q.empty()){
		auto [dn, u] = q.top(); q.pop();
		if(d[u] < -dn) continue;

		for(auto [i, w] : g[u]) if(d[i] > d[u] + w){
			d[i] = d[u] + w;
			q.push({-d[i], i});
		}
	}
}

int main(){ _
	cin >> n >> m;
	g = vector<vector<ii>> (n);
	while(m--){
		int a, b, w; cin >> a >> b >> w;
		a--, b--;
		g[a].pb({b,w}), g[b].pb({a,w});
	}

	int serv; cin >> serv;
	serv--;
	dijkstra(serv);
	
	ll maxi = -LINF;
	ll mini = LINF;

	for(int i = 0; i < n; i++) if(i != serv)
		maxi = max(maxi, d[i]), mini = min(mini, d[i]);

	cout << maxi - mini << endl;
	exit(0);
}
