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
vector<int> w, v;
vector<vector<int>> dp;
int n, k;

int solve(int i, int j){
	if(j > k) return -INF;
	if(i >= n) return 0;
	if(dp[i][j] != -1) return dp[i][j];
	return dp[i][j] = max(solve(i+1, j), solve(i+1, j+w[i]) + v[i]);
}

int main(){ _
	int tt; cin >> tt;
	while(tt--){
		int r;
		cin >> n;
		w.resize(n), v.resize(n);
		for(int i = 0; i < n; i++) cin >> v[i] >> w[i];
		cin >> k >> r;
		dp.assign(n, vector<int> (k+1, -1));
		if(solve(0, 0) >= r) cout << "Missao completada com sucesso\n";
		else cout << "Falha na missao\n";
	}
	exit(0);
}
