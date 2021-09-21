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
const int MOD = 1e9+7;

ll inv(ll a, ll b) {
	return a > 1 ? b - inv(b%a, a)*b/a : 1;
}

ll fact(ll n){
	if(n == 0) return 1LL;
	else return (n * fact(n-1)) % MOD;
}

ll choose(ll a, ll b){
	ll perm = fact(a);
	ll div  = ((fact(b) % MOD) * (fact(a-b) % MOD)) % MOD;
	div     = inv(div, MOD);
	return (perm * div) % MOD;
}

int main(){ _
	int n, m; cin >> n >> m;
	cout << choose(n+2*m-1, 2*m) << endl;
	exit(0);
}
