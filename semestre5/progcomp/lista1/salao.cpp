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
	while(1){
		int aux;
		int cs, ls; cin >> cs >> ls;
		if(cs == 0 and ls == 0) break;
		int lt; cin >> lt;
		int n; cin >> n;
		vector<int> t(1e4 + 10);
		t[0] = INF;

		while(n--){
			int a; cin >> a;
			t[a]++;
		}
		
		int ans = INF;

		// Vertical
		if((ls*100) % lt == 0){
			int rem = (ls*100)/lt;
			int nt = 0;
			
			nt  += min(rem, t[cs]);
			rem -= min(rem, t[cs]);
			for(int i = 1; i <= cs/2; i++){
				if(i == cs-i) aux = min(t[i]/2, rem);
				else aux = min({t[i], t[cs-i], rem});
				
				nt += aux * 2, rem -= aux;
			}

			if(rem == 0) ans = min(nt, ans);
		}

		// Horizontal
		if((cs*100) % lt == 0){
			int rem = (cs*100)/lt;
			int nt = 0;

			nt  += min(rem, t[ls]);
			rem -= min(rem, t[ls]);
			for(int i = 1; i <= ls/2; i++){
				if(i == ls-i) aux = min(t[i]/2, rem);
				else aux = min({t[i], t[ls-i], rem});
				nt += aux * 2, rem -= aux;
			}
			
			if(rem == 0) ans = min(nt, ans);
		}
		
		if(ans == INF) cout << "impossivel" << endl;
		else cout << ans << endl;
	}
	exit(0);
}
