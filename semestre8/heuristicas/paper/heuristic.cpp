#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

struct timer : high_resolution_clock {
	const time_point start;
	timer(): start(now()) {}
	int operator()() {
		return duration_cast<milliseconds>(now() - start).count();
	}
};

const int MAX_T = 1000;
const int MAX = 1e5 + 10;
int label[MAX];
vector<int> graph[MAX];
int n;

vector<int> min_lex(vector<int> &v1, vector<int> &v2) {
	for (int i = 0; i < n; i++) {
		if (label[v1[i]] < label[v2[i]]) return v1;
		else if (label[v2[i]] < label[v1[i]]) return v2;
	}
	return v1;
}

vector<int> pilot(vector<int> pref) {
	vector<int> vis(n), dg_in(n);
	for (int i : pref) vis[i] = 1;
	for (int i = 0; i < n; i++) if (!vis[i]) {
		for (int j : graph[i]) dg_in[j]++;
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	for (int i = 0; i < n; i++) if (!vis[i] and dg_in[i] == 0) {
		pq.push(pair(label[i], i));
	}

	while (pq.size()) {
		auto [l, i] = pq.top();
		pq.pop();
		pref.push_back(i);
		for (int j : graph[i]) {
			dg_in[j]--;
			if (dg_in[j] == 0) {
				pq.push(pair(label[j], j));
			}
		}
	}

	return pref;
}

vector<int> best_neig(vector<int> pref) {
	if (pref.size() == n) {
		return pref;
	}

	vector<int> vis(n), dg_in(n);
	for (int i : pref) vis[i] = 1;
	for (int i = 0; i < n; i++) if (!vis[i]) {
		for (int j : graph[i]) dg_in[j]++;
	}

	vector<int> q;
	int min_label = MAX;
	for (int i = 0; i < n; i++) if (!vis[i] and dg_in[i] == 0) {
		if (label[i] < min_label) {
			q.clear();
			q.push_back(i);
			min_label = label[i];
		}
		else if (label[i] == min_label) {
			q.push_back(i);
		}
	}	
	
	vector<int> best;
	for (int i : q) {
		pref.push_back(i);
		vector<int> cur = pilot(pref);
		if (best.empty()) best = cur;
		else best = min_lex(best, cur);
		pref.pop_back();
	}

	return best;
}


int main() {
	int m; cin >> n >> m;
    cout << fixed << setprecision(16);
	for (int i = 0; i < n; i++) {
		cin >> label[i];
	}
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b; a--, b--;
		graph[a].push_back(b);
	}

	timer T;
	int ini = T();
	vector<int> sol = pilot({});
	while (T() - ini < MAX_T) {
		vector<int> pref = sol;
		int r = n-1;
		for (; r >= 0; r--) {
			pref.pop_back();
			vector<int> cur = best_neig(pref);
			if (min_lex(cur, sol) != sol) {
				sol = cur;
				break;
			}
		}
		if (r == -1) break; // não achou melhor solução
	}

    int j = 0;
    double cost = 0;
    for (int i : sol){
        cost += pow(2, sol.size() - j) * label[i];
        j++;
    }
    cout << log2(cost) << endl;


	exit(0);
}
