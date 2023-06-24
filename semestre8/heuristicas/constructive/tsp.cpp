#include <bits/stdc++.h>

using namespace std;

struct Graph{
    // Vertices Coordinates
    vector<pair<double, double>> vertices;
    // Edge Vector - Tuple(Distance, Vertex 1, Vertex 2)
    vector<tuple<double, int, int>> edges;

    // Calculates distance between two points
    double dist(pair<double, double> v1, pair<double, double> v2){
        auto [x1, y1] = v1;
        auto [x2, y2] = v2;

        return sqrt(abs(x1-x2) * abs(x1-x2) + abs(y1-y2) * abs(y1-y2));    
    }

    // Adds a vertex and all its edges to the graph
    void addVertex(pair<double, double> v){
        int n = vertices.size();
        for(int i = 0; i < n; i++){
            double d = dist(vertices[i], v);
            edges.emplace_back(d, i, n);
        }
        vertices.push_back(v);
    }

    // BFS for detecting cycles
    bool bfs(int ini, vector<vector<int>> &g){  
        vector<bool> vis(vertices.size());

        // Vertex, Incoming Vertex, Distance
        queue<tuple<int, int>> q; 
        q.emplace(ini, -1);
        int d = 0;
        while(not q.empty()){
            auto [v, coming] = q.front(); q.pop();
            vis[v] = true;
            for(int u: g[v]) {
                if(u != coming and vis[u] and d < vertices.size())
                    return false;
                if(not vis[u])
                    q.emplace(u, v), d++;
            }
        }
        return true;
    }

    // TSP computing - Return minimum cost found
    // I decided not to return the vertices list cause we only have the true cost for comparison
    double TSP(){
        int size = int(vertices.size());
        double cost = 0;
        vector<int> degree(size);
        vector<vector<int>> g(size);
        
        sort(edges.begin(), edges.end());
        for(auto [d, u, v]: edges){
            // Adds to the answer
            g[u].push_back(v), g[v].push_back(u);
            if(degree[u] < 2 and degree[v] < 2 and bfs(u, g) and bfs(v, g)) // Accepts
                degree[u]++, degree[v]++, cost += d;
            else // Takes Back
                g[u].pop_back(), g[v].pop_back();
        }

        return cost;
    }
};

int main(){
    Graph G;
    string s; cin >> s;
    while(s != "NODE_COORD_SECTION") cin >> s;
    
    double i, x, y;
    while(cin >> i >> x >> y)
        G.addVertex(make_pair(x, y));
    cout << G.TSP() << endl;
	exit(0);
}