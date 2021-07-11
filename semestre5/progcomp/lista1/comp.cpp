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

void uni(int x, int y){
	x = find(x), y = find(y);
	p[x] = y;
}

int main(){ _
	int tt; cin >> tt;
	for(int t = 1; t <= tt; t++){
		int n, m; cin >> n >> m;
		p = vector<int>(n+1);
		for(int i = 0; i < n+1; i++) p[i] = i;
		while(m--){
			char l1, l2; cin >> l1 >> l2;
			int a = l1 - 'a', b = l2 - 'a';
			uni(a,b);
		}
		
		cout << "Case #" << t << ":" << endl;
		int comp = 0;
		int now = find(0);
		bool stop = false;
		while(!stop){
			comp++;
			stop = true;
			
			vector<char> print;
			for(int i = 0; i < n; i++)
				if(find(i) == now) print.pb(char('a'+i));
			uni(now, n);
			sort(print.begin(), print.end());
			for(char i: print) cout << i << ",";
			cout << endl;
			
			for(int i = 0; i < n; i++){
				if(find(i) != n){
					stop = false;
					now = find(i);
					break;
				}
			}
		}

		cout << comp << " connected components\n\n";
	}
	exit(0);
}
