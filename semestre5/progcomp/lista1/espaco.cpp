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

vector<int> p;

int find(int x){
	return p[x] = (p[x] == x ? x : find(p[x]));
}

bool uni(int x, int y){
	x = find(x), y = find(y);
	if(x == y) return false;
	p[y] = x;
	return true;
}

int main(){ _
	vector<tuple<int, int, int>> ed;
	int m; cin >> m;
	int n = -INF;
	while(m--){
		int a, b, w; cin >> a >> b >> w;
		ed.emplace_back(w,a,b);
		n = max({a,b,n});
	}
	ll ansmin = 0;
	p.assign(n+1, 0);
	for(int i = 0; i < n; i++) p[i] = i;
	sort(ed.begin(), ed.end());
	for(auto [w,a,b]:ed) if(uni(a,b)) ansmin += w;
	for(auto &[w,a,b]: ed) w = -w;

	ll ansmax = 0;
	p.assign(n+1, 0);
	for(int i = 0; i < n; i++) p[i] = i;
	sort(ed.begin(), ed.end());
	for(auto [w,a,b]:ed) if(uni(a,b)) ansmax -= w;
	
	cout << ansmax << endl << ansmin << endl;
	exit(0);
}
