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

vector<vector<int>> c;
int n, k;

void check(){
	for(int i = 0; i < n; i++){
		for(int j = 1; j < 14; j++){
			if(c[i][j] == 4 and accumulate(c[i].begin(), c[i].end(), 0) < 5){
				cout << i+1 << endl;
				exit(0);
			}
		}
	}
}

void play(int p){ // p = who's playin
	int np = (p+1) % n; // next player
	if(c[p][0] == 2) c[p][0]--;
	else if(c[p][0] == 1){
		c[p][0] = 0, c[np][0] = 2; // Passing Joker
		check(), play(np);
	}
	
	for(int j = 1; j <= 4; j++){
		if(j == 3) continue;
		// Passing a card with j ocurrences
		for(int i = 1; i < 14; i++){
			if(c[p][i] == j){
				c[p][i]--, c[np][i]++; // Passing Card
				check(), play(np);
			}
		}
	}
	
	cout << "ERROR ON PLAYER " << p << endl;
	exit(0);
}

int main(){ //_
	cin >> n >> k, k--;
	c.assign(n, vector<int> (14, 0));
	map<char, int> m;

	// Building map
	for(int i = 2; i <= 9; i++) m[char('0'+ i)] = i;
	m['A'] = 1, m['D'] = 10, m['Q'] = 11, m['J'] = 12, m['K'] = 13;
	

	for(int i = 0; i < n; i++){
		string s; cin >> s;
		for(char card: s) c[i][m[card]]++;
	}

	c[k][0] = 2; // Joker

	play(k);
	exit(0);
}
