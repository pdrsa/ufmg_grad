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

int n, k;
double dam;
double dp[1010][110];
vector<double> delta, life;

double solve(int i, int mana){
	if(i == n) return double(0);
	if(dp[i][mana] != -1) return dp[i][mana];

	double a = INF, b = INF;
	a = solve(i+1, mana) + double(life[i] / dam);
	if(mana > 0)
		b = solve(i+1, mana-1) + double(life[i] / (dam + delta[i]));

	return dp[i][mana] = min(a, b);
}

void reset(){
	for(int i = 0; i < 1010; i++)
		for(int j = 0; j < 110; j++)
			dp[i][j] = double(-1);

	delta.assign(n, 0);
	life.assign(n, 0);
}

int main(){ _
	while(cin >> n >> k >> dam){
		reset();
		for(int i = 0; i < n; i++) cin >> life[i] >> delta[i];
	
		cout << fixed << setprecision(4);
		cout << solve(0, k) << endl;
	}
	exit(0);
}
