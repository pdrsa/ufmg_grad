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

	int n;
	while(cin >> n){

		priority_queue<int> pq;
		queue<int> q;
		stack<int> s;
		vector<int> hpq, hq, hs, ht;
		while(n--){
			int op, x; cin >> op >> x;
			if(op == 1) pq.push(x), q.push(x), s.push(x);
			else{
				ht.pb(x);
				hpq.pb(pq.top()), pq.pop();
				hq.pb(q.front()), q.pop();
				hs.pb(s.top()), s.pop();
			}
		}

		int ans = 0;
		if(ht == hpq) ans += 1;
		if(ht == hq) ans += 2;
		if(ht == hs) ans += 4;
	
		if(ans == 0) cout << "impossible" << endl;
		else if(ans == 1) cout << "priority queue" << endl;
		else if(ans == 2) cout << "queue" << endl;
		else if(ans == 4) cout << "stack" << endl;
		else cout << "not sure" << endl;

	}
	exit(0);
}
