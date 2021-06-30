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
	int ans = 0;
	while(1){
		bool primo = true;
		ans += n;
		for(int i = 2; i * i <= n; i++){
			if(n % i == 0){
				//ans += (n/i);
				n /= i;
				primo = false;
				break;
			}
		}
		if(primo) break;
	}
	cout << ans+1 << endl;
	exit(0);
}
