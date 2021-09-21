//JP - Not in Kansas Anymore
#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back

// #define int ll
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll,ll> iill;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAX = 1e7+1;
const int MOD = 1e9+6;

bool prime[MAX];

void sieve() 
{ 
    memset(prime, true, sizeof(prime)); 
	prime[1] = false;
  
    for (int p=2; p*p < MAX; p++) 
    { 
        if (prime[p] == true) 
        { 
			//Everything less than p^2 has already been marked
            for(int i=p*p; i < MAX; i += p) 
                prime[i] = false; 
        }
    }
}



int32_t main(){ _
	sieve();
	int a, b; cin >> a >> b;
	
	if(a == b){
		cout << "?" << endl;
		exit(0);
	}
	
	int np = 0;
	for(int i = min(a, b); i <= max(a, b); i++) np += prime[i];
	if(np == 0){
		cout << "Bob" << endl;
		exit(0);
	}

	int r = abs(a-b), p = (np+r-1);
	int ans = 1;
	for(int i = 0; i < 30; i++){
		int bp = p & (1 << i);
		int bq = r & (1 << i);
		if(bq > bp) ans = 0;
	}
	
	cout << (ans == 1 ? "Alice" : "Bob") << endl;
	exit(0);
}
