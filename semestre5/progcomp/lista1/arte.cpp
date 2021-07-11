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

vector<vector<int>> g;
vector<bool> d;

void dfs(int x){
	d[x] = true;
	for(int u: g[x]) if(!d[u]) dfs(u);
}

int main(){ _
	int m, n; cin >> m >> n;
	int k; cin >> k;
	vector<tuple<int, int, int>> sen;
	g.resize(k+4);

	// Paredes: 
	// 0 = cima, 1 = esquerda, 2 = direita, 3 = baixo
	for(int i = 4; i < k+4; i++){
		int ux, uy, s;
		cin >> ux >> uy >> s;
		// Cima
		if(uy - s <= 0) g[i].pb(0), g[0].pb(i);
		// Esquerda
		if(ux - s <= 0) g[i].pb(1), g[1].pb(i);
		// Direita
		if(ux + s >= m) g[i].pb(2), g[2].pb(i);
		// Baixo
		if(uy + s >= n) g[i].pb(3), g[3].pb(i);
		
		// Outros sensores
		int j = 4;
		for(auto [x, y, ss]: sen){
			int dx, dy;
			dx = abs(x - ux), dy = abs(y - uy);
			if(dx * dx + dy * dy <= (s+ss)*(s+ss))
				g[j].pb(i), g[i].pb(j);
			j++;
		}
		sen.emplace_back(ux, uy, s);
	}


	bool ans = true;
	// Esquerda até Cima ou Direita
	d.assign(k+4, false);
	dfs(1);
	ans = ans and !d[0] and !d[2];
	// Baixo até Cima ou Direita
	d.assign(k+4, false);
	dfs(3);
	ans = ans and !d[0] and !d[2];

	cout << (ans ? "S" : "N") << endl;
	exit(0);
}
