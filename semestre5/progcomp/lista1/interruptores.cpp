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
	int n, m; cin >> n >> m;
	vector<bool> l(m);
	int k; cin >> k;
	vector<vector<int>> it(n);

	while(k--){
		int a; cin >> a;
		a--;
		l[a] = true;
	}

	for(int i = 0; i < n; i++){
		cin >> k;
		while(k--){
			int a; cin >> a;
			a--;
			it[i].pb(a);
		}
	}
	
	for(int j = 0; j < 2; j++){
		for(int i = 0; i < n; i++){
			for(int c: it[i]) l[c] = !l[c];
			bool ok = true;
			for(int c: l) ok = ok and !c;
			if(ok){
				cout << j*n + i + 1 << endl;
				exit(0);
			}
		}
	}

	cout << -1 << endl;

	exit(0);
}
