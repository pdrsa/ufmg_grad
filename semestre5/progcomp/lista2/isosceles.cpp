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
	int n; cin >> n;
	vector<int> l(n), r(n), v(n);
	for(int &i: v) cin >> i;
	l[0] = 1;
	for(int i = 1; i < n; i++) l[i] = min(l[i-1]+1, v[i]);
	r[n-1] = 1;
	for(int i = n-2; i >= 0; i--) r[i] = min(r[i+1]+1, v[i]);
	int ans = 0;
	for(int i = 0; i < n; i++)
		ans = max(ans, min(r[i], l[i]));
	cout << ans << endl;
	exit(0);
}
