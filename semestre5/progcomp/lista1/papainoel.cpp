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
const int LIM = 50;

vector<ii> p; // Value, Weight
vector<vector<int>> dp;
int n;

int solve(int i, int w){
	if(w > 50) return -INF;
	if(i == n) return 0;
	if(dp[i][w] != -1) return dp[i][w];

	return dp[i][w] = max(solve(i+1, w), solve(i+1, w + p[i].s) + p[i].f);
}

int main(){ //_
	int tt; cin >> tt;
	while(tt--){
		cin >> n;
		p.assign(n, {0, 0});
		dp.assign(n+3, vector<int> (55, -1));
		for(auto &i: p) cin >> i.f >> i.s;
		int w = 0, pp = 0, ans = 0;

		for(int i = 0; i < n; i++){
			if(w + p[i].s > 50) continue;
			if(solve(i+1, w + p[i].s) + p[i].f > solve(i+1, w))
				ans += p[i].f, w += p[i].s, pp++;
		}

		cout << ans << " brinquedos\n";
		cout << "Peso: " << w << " kg\n";
		cout << "sobra(m) " << n-pp << " pacote(s)\n\n";
	}
	exit(0);
}
