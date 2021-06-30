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

int main(){ _
	string s; cin >> s;
	vector<int> a, q;
	ll ans = 0;
	for(int i = 0; i < s.size(); i++){
		char c = s[i];
		if(c == 'A') a.pb(i);
		if(c == 'Q') q.pb(i);
	}
	for(int i: q){
		for(int j: a){
			//cout << j << endl;
			if(j <= i) continue;
			auto it = upper_bound(q.begin(), q.end(), j);
			ans += q.end() - it;	
		}
	}
	cout << ans << endl;
	exit(0);
}
