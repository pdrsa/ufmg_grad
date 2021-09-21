//JP - Not in Kansas Anymore
#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back

typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

ll dist(pair<ll, ll> a, pair<ll, ll> b){
	ll dx = abs(a.first  - b.first);
	ll dy = abs(a.second - b.second);
	return dx*dx + dy*dy;
}

int32_t main(){ _
	int n; cin >> n;
	while(n){
		vector<pair<ll, ll>> p(n);
		for(auto &[x,y]: p) cin >> x >> y;
		ll ans = 0;
		for(int i = 0; i < n; i++){
			vector<ll> d;
			for(int j = 0; j < n; j++) if(j != i) d.pb(dist(p[i], p[j]));
			sort(d.begin(), d.end());
			for(int j = 0; j < n; j++) if(j != i){
				ll d1 = dist(p[i], p[j]);
				int a  = lower_bound(d.begin(), d.end(), d1) - d.begin();
				int b = upper_bound(d.begin(), d.end(), d1) - d.begin();
				
				ans += b-a - 1;
			}
		}
		cout << ans/2 << endl;
		cin >> n;
	}
	exit(0);
}
