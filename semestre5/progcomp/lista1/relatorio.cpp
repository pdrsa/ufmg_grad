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

bool isDig(char c){return c >= '0' and c <= '9';}
int np, nv;
vector<string> vend, prod;

bool gotIt;

void printAns(vector<int> val){
	int j = 0;
	for(int i: val){
		cout << i << " ";
		j++;
		if(j % (nv+1) == 0) cout << endl;
	}
}

int sum(vector<int> val, int n){
	int ret = 0;
	reverse(val.begin(), val.end());
	for(int i = 0; i < n; i++) ret += val[i];
	return ret;
}

int calcV(int v, int i, int n){
	string s = prod[v];
	s = s.substr(i, n);
	return stoi(s);
}

void solve(int v, int p, int i, vector<int> val){
	if(gotIt) return;
	if(i >= prod[v].size()) return;

	//cout << v << " " << p << " " << i << " " << prod[v].size() << endl;
	int vp;
	if(v == nv){
		gotIt = true;
		printAns(val);
	}

	if(p == np){
		if(i < prod[v].size() - 4) return;
		vp = calcV(v, i, prod[v].size() - i);
		if(sum(val, np) != vp){
			cout << "FAIL ON:\n";
			printAns(val);
			return;
		}
		else{
			val.pb(vp); solve(v+1, 0, 0, val);
		}
	}

	else{
		for(int j = 1; j <= 3; j++){
			vp = calcV(v, i, j);
			vector<int> nval = val;
			nval.pb(vp);
			solve(v, p+1, i+j, nval);
		}
	}
}

int main(){ _
	int tt; cin >> tt;
	while(tt--){
		string s;
		cin >> s;

		// Reseting
		np = (s.size() - 6)/2; // N de Produtos
		nv = -1; gotIt = false;
		vend = prod = vector<string>();

		while(s[0] != 'T' or s[1] != 'P'){
			cin >> s;
			string v, p;
			for(char c: s){
				if(isDig(c)) p.pb(c);
				else v.pb(c);
			}
			vend.pb(v), prod.pb(p);
			nv++;
		}
		solve(0, 0, 0, vector<int>());
	}
	exit(0);
}
