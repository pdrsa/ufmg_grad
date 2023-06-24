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

    // TSP computing - Return minimum cost found and it's path
    pair<double, vector<int>> TSP(){
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

        // Finds path
        vector<int> path = {0};
        int v = g[0][0], par = 0;
        while(v != 0){
            path.push_back(v);
            for(int u:g[v]) if(u != par){
                par = v;
                v = u;
                break;
            }
        }

        return make_pair(cost, path);
    }
    
    // Calculates cost of a given path
    double calcCost(vector<int> &path){
        double cost = 0;
        for(int i = 0; i < path.size(); i++)
            cost += dist(vertices[path[i]], vertices[path[(i+1)%vertices.size()]]);
        return cost;
    }

    // Receives a solution and develops a new random solution based on the given one
    pair<double, vector<int>> evolve(pair<double, vector<int>> &sol){
        auto [cost, path] = sol;
        // Gets two random nodes to flip them in path
        int v1 = rand() % path.size(), v2 = rand() % path.size();
        while(v2 == v1) v2 = rand() % path.size();
        if(v1 > v2) swap(v1, v2);
        // Constructs new answer
        vector<int> new_path;
        // Copying
        for(int i = 0; i < v1; i++)
            new_path.push_back(path[i]);
        // Flipping
        for(int i = v2; i >= v1; i--)
            new_path.push_back(path[i]);
        // Copying
        for(int i = v2+1; i < path.size(); i++)
            new_path.push_back(path[i]);

        return make_pair(calcCost(new_path), new_path);
    }

    // Receives size of population, number of generations and number of children
    // Return best solution found amongst all evolutions
    pair<double, vector<int>> genetic(int nGenerations, int popSize, int nChildren){
        // Generates first population
        vector<pair<double, vector<int>>> population;
        auto first = TSP();
        population.push_back(first);
        for(int i = 0; i < popSize; i++)
            population.push_back(evolve(first));
        for(int k = 1; k < nGenerations; k++){
            int n = population.size();
            for(int i = 0; i < n; i++){
                for(int j = 0; j < nChildren; j++)
                    population.push_back(evolve(population[i]));
            }
            sort(population.begin(), population.end());
            for(int i = n; i < population.size(); i++)
                population.pop_back();
        }

        return population[0];
    }
};

int main(){
    Graph G;
    string s; cin >> s;
    while(s != "NODE_COORD_SECTION") cin >> s;
    
    double i, x, y;
    while(cin >> i >> x >> y)
        G.addVertex(make_pair(x, y));
    
    auto [cost, path] = G.genetic(5, 20, 30);
    cout << cost << endl;
	exit(0);
}