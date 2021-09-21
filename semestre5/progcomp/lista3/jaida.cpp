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
const int MAX = 2e6 + 50;

bool got[MAX];

int32_t main(){ _
	int tt; cin >> tt;
	while(tt--){
		for(int i = 0; i < MAX; i++) got[i] = false;
		int n; cin >> n;
		vector<int> v(n);
		
		for(int &i: v){
			cin >> i;
			if(i < MAX) got[i] = true;
		}
		
		int ans = (got[1] ? -1 : 0);
		for(int i = 2; i < MAX and ans == -1; i++){
			if(!got[i]) ans = i-1;
			for(int j = i; j < MAX; j += i) got[j] = true;
		}

		cout << ans << endl;
	}
	
	exit(0);
}
