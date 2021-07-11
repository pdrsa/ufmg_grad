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
	string s, c; cin >> s >> c;
	int ans = 0;
	for(int i = 0; i < s.size() - c.size(); i++){
		bool ok = true;
		for(int j = 0; j < c.size(); j++)
			ok = ok and (c[j] != s[i+j]);
		ans += ok;
	}
	cout << ans << endl;
	exit(0);
}
