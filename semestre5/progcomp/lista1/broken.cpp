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
		int m; cin >> m;
		if(m == 0) break;
		cin.ignore();
		//cin.ignore();
		string s;
		getline(cin, s);
		int ans = 0;
		int c = 0;
		map<char, int> ma;
		int l = 0, r = 0;
		while(r < s.size()){
			while(c <= m and r < s.size()){
				if(ma[s[r]] == 0) c++;
				ma[s[r]]++;
				if(c <= m and r < s.size()) ans = max(ans, r-l+1); 
				r++;
			}
			if(c <= m and r < s.size()) ans = max(ans, r-l+1); 
			while(c > m and l < s.size()){
				if(ma[s[l]] == 1) c--;
				ma[s[l]]--;
				l++;
			}
		}
		cout << ans << endl;
	}
	exit(0);
}
