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
const ll P    = -10000000;

vector<ll> clas_t;
vector<int> ten;
vector<int> tem;
vector<int> pro;
int n;


void reset(){
	clas_t = vector<ll>();
	pro = ten = tem = vector<int> ();
}

bool solve(int m){
		vector<ll> v;
		for(int i = 0; i < n; i++)
			v.pb(ll(pro[i])*P + ll(tem[i] + ten[i] * m));
		
		// Coordinate Compression on v
		vector<ll> ov = v;
		sort(ov.begin(), ov.end());
		ov.resize(unique(ov.begin(), ov.end()) - ov.begin());
		for (ll& i : v)
			i = lower_bound(ov.begin(), ov.end(), i) - ov.begin();
		return v != clas_t;
}

int main(){ //_
	int m; cin >> n >> m;
	while(n+m > 0){
		reset();
		// Reading Input
		for(int i = 0; i < n; i++){
			int t = 0, p = 0, pr = 0;
			for(int j = 0; j < m; j++){
				int pa; cin >> pa;
				string s; cin >> s;
				if(s[1] == '-') continue;
				
				pr++;
				s = s.substr(1);
				t += stoi(s);
				p += pa;
			}
			ten.pb(p), tem.pb(t);
			pro.pb(pr);
		}
		
		/*
		for(int i = 0; i < n; i++)
			cout << "Time " << i+1
			<< " Problemas: " << pro[i] << 
			" Tentativas: " << ten[i] <<
			" Tempo: " << tem[i] << endl;
		*/
		
		// Solving for 20a
		for(int i = 0; i < n; i++)
			clas_t.pb(ll(pro[i])*P + ll(tem[i] + ten[i] * 20));
		
		// Coordinate Compression on clas_t
		vector<ll> ov = clas_t;
		sort(ov.begin(), ov.end());
		ov.resize(unique(ov.begin(), ov.end()) - ov.begin());
		for (ll &i : clas_t)
			i = lower_bound(ov.begin(), ov.end(), i) - ov.begin();	
		// Find min
		int ini = 1, fim = 20;
		while(ini < fim){
			int mid = (ini+fim)/2;
			if(solve(mid)) ini = mid+1;
			else fim = mid;
		}
		cout << ini << " ";
		
		// Find max
		ini = 20, fim = 10000;
		while(ini < fim){
			int mid = (ini+fim+1)/2;
			if(solve(mid)) fim = mid-1;
			else ini = mid;
		}
		if (ini == 10000) cout << "*" << endl;
		else cout << ini << endl;
	cin >> n >> m;}
	exit(0);
}
