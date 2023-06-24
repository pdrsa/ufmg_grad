//JP - Not in Kansas Anymore
#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back

vector<vector<int>> g;
int n;

bool check(int x){
    vector<bool> vis(n);
    queue<int> q; q.push(x);
    while(not q.empty()){
        int v = q.front(); q.pop();
        vis[v] = true;
        for(int u: g[v]){
            if(u == x) return false;
            if(not vis[u]) q.push(u);
        }
    }
    return true;
}

int32_t main(){ _
    srand(time(0));
	int m; cin >> n >> m;
    set<pair<int, int>> s;
    g.resize(n);
    cout << n << " " << m << endl;
    for(int i = 0; i < n; i++) cout << rand() % 2 << endl;
    while(m){
        int a = rand() % n;
        int b = rand() % n;
        if(a == b or s.count(make_pair(a, b))) continue;
        g[a].pb(b);
        if(check(a)){
            m--;
            cout << a+1 << " " << b+1 << endl;
            s.insert(make_pair(a, b));
        }
        else g[a].pop_back();
    }
    exit(0);
}
