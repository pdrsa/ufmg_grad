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
	int b; cin >> b;
	char t; cin >> t;
	int c; cin >> c;
	int a = b*100 + c;
	vector<int> v = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 25, 10, 5, 1};
	vector<string> pri = {"100.00", "50.00", "20.00", "10.00",
	"5.00", "2.00", "1.00", "0.50", "0.25", "0.10", "0.05", "0.01"};

	vector<int> ans(12);
	for(int i = 0; i < 12; i++){
		ans[i] = a/v[i];
		a = a % v[i];
	}
	cout << "NOTAS:" << endl;
	for(int i = 0; i < 12; i++){
		if(i == 6) cout << "MOEDAS:" << endl;
		cout << ans[i] << 
		(i < 6 ? (" nota(s)") : (" moeda(s)"))<< " de R$ " << pri[i] << endl;
	}
	exit(0);
}
