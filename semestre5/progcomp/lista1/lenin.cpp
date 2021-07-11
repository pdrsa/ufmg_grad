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

vector<int> d;
vector<vector<ii>> g; // {vizinho, peso}

int n;
 
void dijkstra(int x, int init) {
	for (int i = 0; i < n; i++) d[i] = INF;
	d[x] = init;
	priority_queue<ii> pq;
	pq.push({0,x});
 
	while (!pq.empty()) {
		auto [ndist, u] = pq.top(); pq.pop();
		if (-ndist > d[u]) continue;

		for (auto [idx, w]:g[u]) if (d[idx] > d[u] + w) {
			d[idx] = d[u] + w;
			pq.push({-d[idx], idx});
		}
	}
}

int main(){ _
	while(cin >> n){
		d = vector<int> (n);
		g = vector<vector<ii>> (n);
		int m, bullets; cin >> m >> bullets;
		double p; cin >> p;
		vector<ii> ed(m);
		for(auto &i: ed) cin >> i.f >> i.s;
		int nat; cin >> nat;
		vector<int> at(n);
	
		while(nat--){
			int a; cin >> a;
			at[a-1]++;
		}

		for(auto [a,b]: ed){
			a--; b--;
			g[a].pb({b, at[b]});
			g[b].pb({a, at[a]});
		}
	
		int beg, end; cin >> beg >> end;
		beg--, end--;
		dijkstra(beg, at[beg]);
		int ans = d[end];
		if(ans > bullets) cout << 0.000 << endl;
		else{
			double fans = 1;
			while(ans--) fans *= p;
			cout << fixed << setprecision(3) << fans << endl;
		}
	}
	exit(0);
}
