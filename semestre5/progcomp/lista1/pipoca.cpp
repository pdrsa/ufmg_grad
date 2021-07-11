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

int n, c, t;
vector<int> p;

bool check(ll m){
	ll cr = c, pr = m * t; // Competidores Restantes e Pipocas Restantes

	for(int i = 0; i < n and cr > 0;){
		if(pr >= p[i]) pr -= p[i], i++;
		else pr = m * t, cr--;
	}

	return cr > 0;
}


int main(){ _
	cin >> n >> c >> t;
	p = vector<int> (n);
	for(int &i: p) cin >> i;
	ll l = 1, r = 1e10;

	while(l < r){
		ll m = (l+r)/2;
		if(check(m)) r = m;
		else l = m+1;
	}

	cout << l << endl;
	exit(0);
}
