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

int n, m;
vector<ii> v;
map<vector<int>, int> dp;

bool solve(vector<int> c){
	for(int i = 1; i <= 6; i++) if(c[i] > n) return false;
	if(c[0] == m) return true;
	if(dp.count(c)) return dp[c];
	
	vector<int> a; a = c; a[0]++; a[v[c[0]].f]++;
	vector<int> b; b = c; b[0]++; b[v[c[0]].s]++;

	return dp[c] = solve(a) or solve(b);
}

int main(){ _
	int tt; cin >> tt;
	map<string, int> c;
	c["XS"] = 1, c["S"] = 2, c["M"] = 3, c["L"] = 4, c["XL"] = 5, c["XXL"] = 6;
	while(tt--){
		v.clear();
		dp.clear();
		cin >> n >> m;
		n /= 6;
		for(int i = 0; i < m; i++){
			string a, b; cin >> a >> b;
			v.pb({c[a], c[b]});
		}
		vector<int> ini = {0, 0, 0, 0, 0, 0, 0};
		cout << (solve(ini) ? "YES" : "NO") << endl;
	}
	exit(0);
}
