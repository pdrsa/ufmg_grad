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

bool prime[MAX];
vector<int> primes;

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


    primes.pb(1);
	for(int i = 2; i < MAX; i++) if(prime[i]) primes.pb(i);
}



int32_t main(){ _
	sieve();
	int tt; cin >> tt;
	while(tt--){
		int n; cin >> n;
		set<int> num;

		while(n--){
			int a; cin >> a;
			num.insert(a);
		}
			
		for(int i: primes){
			if(!num.count(i)){
				cout << i-1 << endl;
				break;
			}
		}
	}
	exit(0);
}
