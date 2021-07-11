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


bool equal(vector<string> a, vector<string> b){
	for(int i = 0; i < a.size(); i++)
		for(int j = 0; j < a[i].size(); j++)
			if(a[i][j] != b[i][j]) return false;

	return true;
}

int main(){ _
	vector<vector<string>> bra(10);

	bra[0].pb(".*"), bra[0].pb("**");
	bra[1].pb("*."), bra[1].pb("..");
	bra[2].pb("*."), bra[2].pb("*.");
	bra[3].pb("**"), bra[3].pb("..");
	bra[4].pb("**"), bra[4].pb(".*");
	bra[5].pb("*."), bra[5].pb(".*");
	bra[6].pb("**"), bra[6].pb("*.");
	bra[7].pb("**"), bra[7].pb("**");
	bra[8].pb("*."), bra[8].pb("**");
	bra[9].pb(".*"), bra[9].pb("*.");

	while(1){
		int n; cin >> n; if(!n) break;
		char type; cin >> type;
		
		if(type == 'S'){
			string s; cin >> s;
			for(int j = 0; j < 3; j++){
				for(int i = 0; i < s.size(); i++){
					cout << ((j == 2) ? ".." : bra[int(s[i] - '0')][j]);
					if(i != s.size() - 1) cout << " ";
				}
				cout << endl;
			}
		}

		else{
			vector<vector<string>> inp(n, vector<string>(2));
			for(int j = 0; j < 3; j++){
				for(int i = 0; i < n; i++){
					string l; cin >> l;
					if(j < 2)  inp[i][j] = l;
				}
			}

			for(auto s: inp)
				for(int i = 0; i < 10; i++)
					if(equal(s, bra[i])) cout << i;
			cout << endl;
		}
	}


	exit(0);
}
