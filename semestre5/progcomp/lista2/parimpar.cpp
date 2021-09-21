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

int dp[1010][1010];
vector<int> v(1010);

int solve(int i, int j, int p){
	if(dp[i][j] != -1) return dp[i][j];
	if(i > j) return 0;

	if(p == 0){
		return    dp[i][j] = max(solve(i+1, j, 1) + !(v[i] % 2),
								    solve(i, j-1, 1) + !(v[j] % 2));

	} else return dp[i][j] = min(solve(i+1, j, 0), solve(i, j-1, 0));
}

void reset(){
	for(int i = 0; i < 1010; i++)
		for(int j = 0; j < 1010; j++)
			dp[i][j] = -1;
	
	for(int &i: v) i = 0;
}

int main(){ _
	int n; cin >> n;
	while(n > 0){
		n *= 2;
		reset();

		for(int i = 0; i < n; i++) cin >> v[i];
		cout << solve(0, n-1, 0) << endl;

		cin >> n;
	}
	exit(0);
}
