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

int n, m, x, y;
int dp[3][101][101][21][21];
int v[101][101];

// 0 is free, 1 is going left and 2 is going right
int solve(int move, int i, int j, int nulls, int negatives){
	int &memo = dp[move][i][j][nulls][negatives];
	
	if(nulls > x or negatives > y) return INF;
	if(memo != INF) return memo;
	if(i == n-1 and j == m-1) return v[i][j];
	
	// Cell atributes
	int null = nulls     + (v[i][j] == 0);
	int neg  = negatives + (v[i][j] < 0);

	int a = INF, b = INF, c = INF;
	
	if(i < n-1)               a = solve(0, i+1, j, null, neg); // Go down
	if(j > 0   and move != 2) b = solve(1, i, j-1, null, neg); // Go left
	if(j < m-1 and move != 1) c = solve(2, i, j+1, null, neg); //Go right

	return memo = min({a, b, c}) + v[i][j];
}

void reset(){
	for(int mv = 0; mv < 3; mv++)
	for(int i = 0; i < n+1; i++) for(int j = 0; j < m+1; j++)
	for(int k = 0; k < x+1; k++) for(int l = 0; l < y+1; l++)
		dp[mv][i][j][k][l] = INF;
}

int32_t main(){ _
	while(cin >> n >> m >> x >> y){
		reset();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				cin >> v[i][j];
		
		int ans = solve(0, 0, 0, 0, 0);
		if(ans < 1e8) cout << ans << endl;
		else cout << "Impossivel" << endl;
	}
	exit(0);
}
