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

int n;
int dp[101][101][101];
vector<vector<int>> p(3);

bool solve(int i, int j, int k){
	if(i == n and j == n and k == n) return 1;
	if(dp[i][j][k] != -1) return dp[i][j][k];
	bool ans = false;
	
	int p1 = p[0][i], p2 = p[1][j], p3 = p[2][k];

	// 100
	if(i < n and p1 % 3 == 0)
		ans = ans or bool(solve(i+1, j, k));
	// 010
	if(j < n and p2 % 3 == 0)
		ans = ans or bool(solve(i, j+1, k));
	// 001
	if(k < n and p3 % 3 == 0)
		ans = ans or bool(solve(i, j, k+1));
	// 101
	if(i < n and k < n and (p1+p3) % 3 == 0)
		ans = ans or bool(solve(i+1, j, k+1)); 
	// 110
	if(i < n and j < n and (p1+p2) % 3 == 0)
		ans = ans or bool(solve(i+1, j+1, k));
	// 011
	if(j < n and k < n and (p2+p3) % 3 == 0)
		ans = ans or bool(solve(i, j+1, k+1));
	// 111
	if(i < n and j < n and k < n and (p1+p2+p3) % 3 == 0)
		ans = ans or bool(solve(i+1, j+1, k+1));

	return dp[i][j][k] = int(ans);
}

int main(){ _
	cin >> n;
	while(n){
		p.assign(3, vector<int> (n));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < 3; j++){
				cin >> p[j][i];
			}
		}

		for(int i = 0; i <= 100; i++)
			for(int j = 0; j <= 100; j++)
				for(int k = 0; k <= 100; k++)
					dp[i][j][k] = -1;

		cout << solve(0, 0, 0) << endl;
		cin >> n;
	}
	exit(0);
}
