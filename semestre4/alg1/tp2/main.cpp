#include <bits/stdc++.h>

using namespace std;
vector<int> id, sz;

int find(int x){
    return id[x] = (id[x] == x ? x : find(id[x]));
}

bool uni(int x, int y){
    x = find(x), y = find(y);
    if(x == y) return false;
    if(sz[x] > sz[y]) swap(x, y);
    id[x] = y;
    sz[y] += sz[x];
    return true;
}

int main(){
    int n, t; cin >> n >> t;

    //Initialize Union-Find data
    id = vector<int> (n);
    sz = vector<int> (n, 1);
    iota(id.begin(), id.end(), 0);
    
    vector<int> p(n);
    for(int &i:p) cin >> i;
    vector<tuple<int, int, int, int>> e(t);
    
    for(auto &[w, l, a, b]: e){
        cin >> a >> b >> w;
        l = -p[a] - p[b];
    } 
    
    sort(e.begin(), e.end());
    int cus = 0, lu = 0;
    for(auto [w, l, a, b]: e){
        if(uni(a,b)){
            cus += w, lu -= l; 
        }
    }
    cout << cus << " " << lu << endl;
    exit(0);
}
