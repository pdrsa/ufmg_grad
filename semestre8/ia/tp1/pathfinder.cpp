#include <bits/stdc++.h>
using namespace std;

struct Graph{
    int lines, columns;

    // Constants
    const double INF = (1 << 30);
    const pair<int, int> NONE = {-1, -1};

    // Cost storing map
    vector<vector<double>> terrain;

    // Map for conversion from char to double
    map<char, double> cost = 
    {
        {'.', 1.0}, 
        {';', 1.5}, 
        {'+', 2.5},
        {'x', 6.0},
        {'@', INF}
    };

    // Moviment vector
    vector<pair<int, int>> mv = 
    {
        {-1, 0}, 
        {0, -1}, 
        {0, 1}, 
        {1, 0}
    };

    // Constructor
    Graph(int l, int c){
        terrain = vector<vector<double>> (l, vector<double> (c));
        lines = l, columns = c;
    }

    // Set value on Graph map
    void attribute(int i, int j, int type){
        if(cost.count(type))
            terrain[i][j] = cost[type];
        else
            throw invalid_argument("Map with unknown characters.");
    }

    // Check if position is valid
    bool valid(int x, int y){
        return x >= 0 and x < lines and y >= 0 and y < columns and terrain[x][y] < INF;
    }

    // Manhattan Distance - Name is kept as h for independence in need of changing the heuristic
    double h(int ax, int ay, int bx, int by){
        return abs(ax - bx) + abs(ay - by);
    }

    // Retrieves path given initial vertex, final vertex and parents
    vector<pair<int, int>> retrieve_path(
        int xi, int yi, int xf, int yf, 
        vector<vector<pair<int, int>>> &parent
        ){
        
        vector<pair<int, int>> path;
        while(parent[xf][yf] != NONE){
            path.emplace_back(xf, yf);
            tie(xf, yf) = parent[xf][yf];
            if(xf == xi and yf == yi) path.emplace_back(xi, yi);
        }
        reverse(path.begin(), path.end());

        return path;
    }

    // Breadth First Search
    pair<double, vector<pair<int, int>>> BFS(int xi, int yi, int xf, int yf){
        vector<vector<pair<int, int>>> parent(lines, vector<pair<int, int>>(columns, NONE));
        vector<vector<double>> dist(lines, vector<double>(columns, INF));
        
        // Initialize
        queue<pair<int,int>> frontier;
        dist[xi][yi] = 0;
        frontier.push({xi, yi});
        // Searching
        while(not frontier.empty()){
            auto [x, y] = frontier.front(); frontier.pop();
            if(x == xf and y == yf) break;
            
            for(auto [dx, dy]: mv){
                int x2 = x + dx, y2 = y + dy;
                if(valid(x2, y2) and parent[x2][y2] == NONE and (x2 != xi or y2 != yi)){
                    parent[x2][y2] = {x, y};
                    dist[x2][y2] = dist[x][y] + terrain[x2][y2];
                    frontier.emplace(x2, y2);
                }
            }
        }

        return make_pair(dist[xf][yf], retrieve_path(xi, yi, xf, yf, parent));
    }

    // Greedy
    pair<double, vector<pair<int, int>>> Greedy(int xi, int yi, int xf, int yf){
        set<pair<int, int>> vis;
        vector<pair<int, int>> path;

        // Initialize
        double distance = 0;
        int x = xi, y = yi;
        path.emplace_back(x, y);
        while(x != xf or y != yf){
            // Find best according to heuristic
            double mini = INF;
            pair<int, int> best;
            for(auto [dx, dy]: mv){
                int x2 = x + dx, y2 = y + dy;
                if(valid(x2, y2) and h(x2, y2, xf, yf) < mini){
                    mini = h(x2, y2, xf, yf);
                    best = make_pair(x2, y2);
                }
            }

            if(vis.count(best))
                throw invalid_argument("Infinite loop on greedy search.");
            distance += terrain[best.first][best.second];
            path.push_back(best);
            vis.insert(best);
            tie(x, y) = best;
        }

        return make_pair(distance, path);
    }

    // Dijkstra Algorithm
    pair<double, vector<pair<int, int>>> UCS(int xi, int yi, int xf, int yf){
        vector<vector<pair<int, int>>> parent(lines, vector<pair<int, int>>(columns, NONE));
        vector<vector<double>> dist(lines, vector<double>(columns, INF));
        
        // Ascending order Priority Queue
        priority_queue<
            tuple<double, int,int>, 
            vector<tuple<double, int, int>>, 
            greater<>
        > frontier;

        // Initializing
        dist[xi][yi] = 0;
        frontier.emplace(dist[xi][yi], xi, yi);
        // Searching
        while(not frontier.empty()){
            auto [dist_now, x, y] = frontier.top(); frontier.pop();
            if(dist_now > dist[x][y]){
                if(x == xf and y == yf) break;
                else continue;
            }
            
            for(auto [dx, dy]: mv){
                int x2 = x + dx, y2 = y + dy;
                if(valid(x2, y2) and dist[x2][y2] > dist[x][y] + terrain[x2][y2]){
                    parent[x2][y2] = {x, y};
                    dist[x2][y2] = dist[x][y] + terrain[x2][y2];
                    frontier.emplace(dist[x2][y2], x2, y2);
                }
            }
        }

        return make_pair(dist[xf][yf], retrieve_path(xi, yi, xf, yf, parent));
    }

    // A* Algorithm
    pair<double, vector<pair<int, int>>> Astar(int xi, int yi, int xf, int yf){
        vector<vector<pair<int, int>>> parent(lines, vector<pair<int, int>>(columns, NONE));
        vector<vector<double>> dist(lines, vector<double>(columns, INF));
        
        // Ascending order Priority Queue
        priority_queue<
            tuple<double, int,int>, 
            vector<tuple<double, int, int>>, 
            greater<>
        > frontier;

        // Initializing
        dist[xi][yi] = 0;
        frontier.emplace(dist[xi][yi], xi, yi);
        // Searching
        while(not frontier.empty()){
            auto [dist_now, x, y] = frontier.top(); frontier.pop();
            if(dist_now - h(x, y, xf, yf) > dist[x][y]){
                if(x == xf and y == yf) break;
                else continue;
            }

            for(auto [dx, dy]: mv){
                int x2 = x + dx, y2 = y + dy;
                if(valid(x2, y2) and dist[x2][y2] > dist[x][y] + terrain[x2][y2]){
                    parent[x2][y2] = {x, y};
                    dist[x2][y2] = dist[x][y] + terrain[x2][y2];
                    frontier.emplace(dist[x2][y2] + h(x2, y2, xf, yf), x2, y2);
                }
            }
        }

        return make_pair(dist[xf][yf], retrieve_path(xi, yi, xf, yf, parent));
    }

    // Maximum Depth Search
    pair<double, vector<pair<int, int>>> MDS(int xi, int yi, int xf, int yf, int lim){
        vector<vector<pair<int, int>>> parent(lines, vector<pair<int, int>>(columns, NONE));
        vector<vector<double>> dist(lines, vector<double>(columns, INF));
        
        // Initialize
        stack<pair<int,int>> frontier;
        dist[xi][yi] = 0;
        frontier.push({xi, yi});
        // Searching
        while(not frontier.empty()){
            auto [x, y] = frontier.top(); frontier.pop();
            if(x == xf and y == yf) break;
            
            for(auto [dx, dy]: mv){
                int x2 = x + dx, y2 = y + dy;
                if(valid(x2, y2) and parent[x2][y2] == NONE and (x2 != xi or y2 != yi)){
                    parent[x2][y2] = {x, y};
                    dist[x2][y2] = dist[x][y] + terrain[x2][y2];
                    if(dist[x2][y2] <= lim)
                        frontier.emplace(x2, y2);
                }
            }
        }

        return make_pair(dist[xf][yf], retrieve_path(xi, yi, xf, yf, parent));
    }

    // Iterative Depth Search
    pair<double, vector<pair<int, int>>> IDS(int xi, int yi, int xf, int yf){
        int maximum_depth = lines * columns;
        for(int depth = 1; depth <= maximum_depth; depth++){
            auto [dist, path] = MDS(xi, yi, xf, yf, depth);
            if(dist < INF) return make_pair(dist, path);
        }

        return make_pair(INF, vector<pair<int, int>>());
    }
};

int main(int argc, char** argv){
    char* file  = argv[1];
    string id   = argv[2];
    int yi      = atoi(argv[3]);
    int xi      = atoi(argv[4]);
    int yf      = atoi(argv[5]);
    int xf      = atoi(argv[6]);
    freopen(file, "r", stdin);
    int lines, columns;
    cin >> columns >> lines;
    Graph G(lines, columns);
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            char c; cin >> c;
            G.attribute(i, j, c);
        }
    }
    
    double answer;
    vector<pair<int, int>> path;
    if(id == "UCS")
        tie(answer, path) = G.UCS(xi, yi, xf, yf);
    if(id == "BFS")
        tie(answer, path) = G.BFS(xi, yi, xf, yf);
    if(id == "IDS")
        tie(answer, path) = G.IDS(xi, yi, xf, yf);
    if(id == "Greedy")
        tie(answer, path) = G.Greedy(xi, yi, xf, yf);
    if(id == "Astar")
        tie(answer, path) = G.Astar(xi, yi, xf, yf);
    
    cout << answer << " ";
    for(auto x: path) cout << "(" << x.second << "," << x.first << ") ";
    cout << endl;
    return 0;
}