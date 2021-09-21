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

vector<int> pre;
int n;
bool ans = false;

void dfs(int i, int wa, int wb){
	if(ans) return;
	if(abs(wa - wb) > 5) return;
	
	if(i == n){
		ans = true;
		return;
	}

	dfs(i+1, wa+pre[i], wb);
	dfs(i+1, wa, wb+pre[i]);
}

int main(){ _
	int tt; cin >> tt;
	while(tt--){
		cin >> n;
		ans = false;
		pre.assign(n, 0);
		for(int i = 0; i < n; i++) cin >> pre[i];
		dfs(0, 0, 0);
		vector<string> resp = {"Ho Ho Ho!", "Feliz Natal!"};
		cout << resp[int(ans)] << endl;
	}
	exit(0);
}
