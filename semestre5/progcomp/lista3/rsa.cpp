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


const int MAX = 2e5+1;
bool prime[MAX];

vector<ll> primes;

ll inv(ll a, ll b){
	if(a > 1) return b - (inv(b % a, a) * b/a);
	else return 1;
}

ll fexp(ll a, ll b, ll m) {
	if (b == 0) return 1;
	ll ret = fexp(a*a % m, b/2, m);

	if(b % 2 == 0) return ret;
	else return a*ret % m;
}


void sieve() 
{ 
    memset(prime, true, sizeof(prime)); 
	prime[1] = false;

    for (int p=2; p*p < MAX; p++) 
    { 
        if (prime[p] == true) 
        { 
            for(int i=p*p; i < MAX; i += p) 
                prime[i] = false; 
        }
    }

	for(int p=2;p < MAX; p++)
		if(prime[p]) primes.pb(p);
} 


int32_t main(){ _
	sieve();
	ll n, e, c; cin >> n >> e >> c;
	int p = 0, q = 0;
	
	for(ll i: primes) if(n % i == 0) p = i, q = n/i;

	ll tot = (p-1)*(q-1), d   = inv(e, tot), m   = fexp(c, d, n);
	cout << m << endl;

	exit(0);
}
