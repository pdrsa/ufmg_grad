	//JP - Not in Kansas Anymore
#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back

typedef long long ll;
typedef pair<double, double> ii;
typedef pair<ll,ll> iill;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

ii mid(ii a, ii b){
	return {(a.f+b.f)/2, (a.s+b.s)/2};
}

int main(){ _
	int n; cin >> n;
	vector<ii> points(n);
	for(auto &[x,y]: points) cin >> x >> y;

	if(n % 2 == 1){
		cout << "NO" << endl;
		exit(0);
	}
	
	ii center;

	for(int i = 0; i < n; i++){
		ii a    = points[i];
		ii b    = points[(i + n/2) % n];
		
		if(i == 0) center = mid(a, b);
		else{
			if(mid(a, b) != center){
				cout << "NO" << endl;
				exit(0);
			}
		}
	}
	
	cout << "YES" << endl;
	exit(0);
}
