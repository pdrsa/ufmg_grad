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
	set<ll> fat;
	ll n; cin >> n;

	for(ll i = 2; i * i <= n; i++){
		while((n % i) == 0){
			n /= i; 
			fat.insert(i);
		}
	}
	if(n != 1) fat.insert(n);
	ll s = fat.size();
	//cout << s << endl;
	cout << (1LL << s) - s - 1 << endl;
	exit(0);
}
