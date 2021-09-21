//JP - Not in Kansas Anymore
#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back

// #define int ll
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll,ll> iill;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
int n, b;

int v[250];
int vb[250];
int dp[126][252][252];

int calc(int nB, int i){
	return vb[nB] * (v[i] + v[(i+1)%n]);
}

int solve(int i, int ini, int fim){
	if(i == b) return 0;
	if(ini == fim or (ini+1)%n == fim) return INF;
	if(dp[i][ini][fim] != -INF) return dp[i][ini][fim];
	
	int pega = solve(i+1, (ini+2)%n, fim) + calc(i, ini);
	int nPega = solve(i, (ini+1)%n, fim);

	return dp[i][ini][fim] = min(pega, nPega);
}

void reset(){
	for(int i = 0; i < b; i++)
		for(int j = 0; j < n; j++)
			for(int k = 0; k < n; k++)
				dp[i][j][k] = -INF;
}

int32_t main(){ _
	while(1){
		cin >> n >> b;
		if(n + b == 0) break;
		reset();

		for(int i = 0; i < n; i++) cin >> v[i];
		for(int i = 0; i < b; i++) cin >> vb[i];
		int fAns = INF;
		for(int i = 0; i < n; i++){
			fAns = min(fAns, solve(1, (i+2)%n, i) + calc(0, i));
		}

		cout << -fAns << endl;
	}
	exit(0);
}
