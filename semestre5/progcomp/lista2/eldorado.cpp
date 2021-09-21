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
const ll MOD  = 1e18;

int n, m;
vector<int> v;
vector<vector<ll>> dp(110, vector<ll>(110, -1));

ll solve(int i, int k){
	if(dp[i][k] != -1) return dp[i][k];
	if(k == 1) return 1;

	ll ans = 0;
	for(int j = i+1; j < n; j++) if(v[j] > v[i]) ans += solve(j, k-1);

	return dp[i][k] = ans;
}

int main(){ _
	cin >> n >> m;
	while(n + m > 0){
		for(auto &s: dp) s.assign(110, -1);
		v.resize(n); for(int &i: v) cin >> i;
		ll ans = 0;
		for(int i = 0; i < n; i++)
			ans += solve(i, m);
		cout << ans << endl;
		cin >> n >> m;
	}
	exit(0);
}
