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
const ll MOD = 1e6;

// Matrix Fast Exponentiation 
typedef vector<vector<ll>> matrix;

matrix id(int size) { // Identity
	matrix A(size, vector<ll>(size, 0));
	for(int i = 0; i < size; i++) A[i][i] = 1;
	return A;
}

matrix mult(matrix& A, matrix& B, ll mod) {
	if(A[0].size() != B.size()) throw invalid_argument("Invalid size on matrices!");

	int n = A.size(), m = B[0].size(), u = A[0].size();
	matrix C(n, vector<ll>(m, 0));

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			for(int k = 0; k < A[0].size(); k++){
				A[i][k] %= mod, B[k][j] %= mod;
				C[i][j] += A[i][k] * B[k][j];
				C[i][j] %= mod;
			}

	return C;
}

matrix fexp(matrix A, ll exp, ll mod) {
	if(exp == 0) return id(A.size());
	matrix B = fexp(mult(A, A, mod), exp / 2, mod); // A squared^(exp / 2)

	if(exp % 2) B = mult(B, A, mod); // If exp'is odd
	return B; 
}

int32_t main(){ _
	ll N, K, L;
	while(cin >> N >> K >> L){
		N /= 5;
		matrix M = {{0LL, L}, {1LL, K}};
		M = fexp(M, N, MOD);
		K %= MOD, L %= MOD;

		cout << fixed << setfill('0') << setw(6);
		cout << (M[0][0] % MOD + (K* (M[1][0] % MOD) % MOD)) % MOD << endl;
	}
	exit(0);
}
