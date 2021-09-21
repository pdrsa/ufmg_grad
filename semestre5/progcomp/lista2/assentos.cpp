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

int32_t main(){ _
	while(1){
		int n, m, need; cin >> n >> m >> need;
		if(n+m+need == 0) break;

		vector<vector<bool>> v(n, vector<bool> (m));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				char a; cin >> a;
				v[i][j] = int(a == '.');
			}
		}
		
		int fAns = INF;
		for(int i = 0; i < n; i++){
			vector<int> dp(m);
			for(int j = i; j < n; j++){
				for(int k = 0; k < m; k++) dp[k] += v[j][k];
				int seats = 0;
				// Two Pointers
				for(int l = 0, r = 0; r < m; r++){
					seats += dp[r];
					while(seats >= need){
						fAns = min(fAns, (r-l+1)*(j-i+1));
						seats -= dp[l]; l++;
					}
				}
			}
		}

		cout << fAns << endl;
	}
	exit(0);
}
