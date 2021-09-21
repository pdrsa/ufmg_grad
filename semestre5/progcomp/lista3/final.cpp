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

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

struct pt {
	double x, y;
	
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}

	bool operator < (const pt p) const {
		if (x != p.x) return x < p.x;
		if (y != p.y) return y < p.y;
		return 0;
	}

	bool operator == (const pt p) const {
		return x == p.x and y == p.y;
	}

}; // Estrutura simples

bool cmp(pt a, pt b) { // Comparador para ordenar
	return a.x < b.x or (a.x == b.x and a.y < b.y);
}

bool clock(pt a, pt b, pt c) { // Retorna se os pontos estão em ordem horária
	return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool cclock(pt a, pt b, pt c) { // Retorna se os pontos estão em ordem anti-horária
	return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

// Algoritmo de Graham lá ce ta ligado né
// divide o bagulho em 2 com os pontos mais
// distantes depois vai construindo uns
// subconjuntos mucho loko.

vector<pt> convexHull(vector<pt>& v) {
	int n = v.size();
	if(n == 1) return v;

	sort(v.begin(), v.end(), &cmp);
	pt p1 = v[0], p2 = v[v.size()-1];
	vector<pt> a, b;
	a.pb(p1); b.pb(p1);
	for (int i = 1; i < v.size(); i++) {
		
		// Up Set
		if ((i == v.size() - 1) or (clock(p1, v[i], p2))) {
			while (a.size() >= 2 and
				   !clock(a[a.size()-2], a[a.size()-1], v[i]))
					a.pop_back();
			a.pb(v[i]);
		}

		// Down Set
		if ((i == v.size() - 1) or (cclock(p1, v[i], p2))) {
			while(b.size() >= 2 and
			!cclock(b[b.size()-2], b[b.size()-1], v[i]))
				b.pop_back();
			b.pb(v[i]);
		}
	}

	// Gather Answer
	vector<pt> ans;
	for (int i = 0; i < a.size(); i++) ans.pb(a[i]);
	for (int i = b.size() - 2; i > 0; i--) ans.pb(b[i]);
	
	return ans;
}

double dist(pt a, pt b){
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y-b.y));
}

bool between(pt a, pt c, pt b){
   	return abs(dist(a, c) + dist(c,b) - dist(a,b)) <= 1e-6;
}

bool has(vector<pt> b, pt a){
	for(int i = 0; i < b.size(); i++)
		if(a == b[i] or between(b[i], a, b[((i+1) % b.size())]))
			return true;
	return false;
}

bool ch(vector<pt> v){
	for(int i = 0; i < v.size(); i++) if(v[i].x != 0 or v[i].y != 0) return true;
	return false;
}

double area(pt a, pt b, pt c) {
  return abs(((a.x - c.x) * (b.y - c.y)) - ((a.y - c.y) * (b.x - c.x)));
}

int32_t main(){ _
	vector<pt> v(5); for(pt &i: v) cin >> i;
	while(ch(v)){
		double ans = 0;
		vector<int> perm(5);
		for(int i = 0; i < 5; i++) perm[i] = i;
		do{
			vector<pt> q = {v[perm[0]], v[perm[1]], v[perm[2]], v[perm[3]]};
			vector<pt> c = convexHull(q);
			if(c.size() < 4) continue;
			/*cout << "Testing for " << endl;
			cout << c[0].x << " " << c[0].y << endl;
			cout << c[1].x << " " << c[1].y << endl;
			cout << c[2].x << " " << c[2].y << endl;
			cout << c[3].x << " " << c[3].y << endl;
			cout << "Area: " << a << endl << endl;
			*/
			double a = area(c[0], c[1], c[2])/2 + area(c[0], c[3], c[2])/2;
			ans = max(ans, a);
		} while(next_permutation(perm.begin(), perm.end()));
		cout << ans << endl;
		for(pt &i: v) cin >> i;
	}
	exit(0);
}
