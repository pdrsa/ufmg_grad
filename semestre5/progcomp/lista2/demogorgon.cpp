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

int n, p;
vector<int> d, c;
vector<vector<int>> dp;

int solve(int i, int hp){
	if(hp <= 0) return 0;
	if(i >= n) return INF;
	if(dp[i][hp] != -1) return dp[i][hp];

	return dp[i][hp] = min(solve(i+1, hp), solve(i+1, hp-d[i]) + c[i]);
}

int main(){ //_
	while(cin >> n >> p){
		d.resize(n), c.resize(n);
		dp.assign(n, vector<int> (p+10, -1));
		for(int i = 0; i < n; i++) cin >> d[i] >> c[i];
		cout << (solve(0, p) < INF ? solve(0, p) : -1) << endl;
	}
	exit(0);
}
