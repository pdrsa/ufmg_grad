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
bool DONE;
vector<ll> ans, revans;
int si;

void dobra(vector<ll> f, int d){
	if(DONE) return;

	int s = f.size();
	int n = abs(max(s - (d + 1), d+1));
	vector<ll> nf(n);

	for(int i = 0; i < n; i++){
		int idx  = n-(i+1);
		int pos1 = (d-i); 
		if(pos1 >= 0) nf[idx]  += f[pos1];

		int pos2 = (d + i + 1);
		if(pos2 < s) nf[idx] += f[pos2];
	}
	
	if(nf == ans or nf == revans) DONE = true;
	for(int i = 0; i < n-1; i++) dobra(nf, i);
}

int main(){ //_
	while(cin >> si){
		vector<ll> f(si);
		for(ll &i: f) cin >> i;
		
		int si2; cin >> si2;
		ans = vector<ll>(si2);
		for(ll &i: ans) cin >> i;
		revans = ans, reverse(revans.begin(), revans.end());
		
		DONE = (f == ans or f == revans);
		for(int i = 0; i < si - 1; i++) dobra(f, i);
		cout << (DONE ? "S" : "N") << endl;
	}
	
	exit(0);
}
