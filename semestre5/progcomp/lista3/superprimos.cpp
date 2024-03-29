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

int divi[MAX];
int ans[MAX];

int32_t main(){ _
	for(int i = 0; i < MAX; i++) divi[i] = 1;
	for(int i = 2; i < MAX; i++)
		for(int j = i; j < MAX; j += i)
			divi[j]++;

	int n;
	while(cin >> n){
		string ans = "Nada";
		if(divi[n] == 2){
			ans = "Super";
			while(n > 0){
				cout << n%10 << " ";
				if(divi[n%10] != 2) ans = "Primo";
				n /= 10;
			}
		}
		cout << ans << endl;
	}
	exit(0);
}
