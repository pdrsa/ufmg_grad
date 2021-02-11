#include <vector>
#include <queue>
using namespace std;

class Graph{
    public:
        Graph(int sz);
        // Adiciona aresta de x à y
        void AddEdge(int x, int y);
        // Adiciona x à lista de PVs adjacentes à CDs
        void AddSource(int x);
        // Calcula a distância de todos os PVs até o CD mais próximo
        void CalcDist();
        // Função auxiliar para checar a existência de ciclos
        void Dfs(int x);
        // Checa se existe um ciclo
        void CheckCycle();
        // Vetor que guarda a Distância até a Source mais próxima
        vector<int> dist;        
        // Quantidade de PVs
        int size;
        // Indica se existe um ciclo no grafo
        bool hasCycle;
    protected:
        // Vetor com os PVs que tem ligação direta à um Centro de Distribuição
        vector<int> sources;
        // Vetor de Vetores de Adjacência de cada PV
        vector<vector<int>> adj;
        // Vetor que guarda a cor de cada PV (Utilizado no algoritmo para encontrar ciclos)
        vector<int> color;
};

Graph::Graph(int sz){
    size  = sz;
    hasCycle = false;
    adj.resize(size);
}

void Graph::AddEdge(int x, int y){
    adj[x].push_back(y);
}

void Graph::AddSource(int x){
    sources.push_back(x);
}

void Graph::CalcDist(){
    // Precisamos iniciar as distâncias como "Infinito". Aqui usarei 1000 pois sabemos que a distância máxima para os testes é 100.
    dist.assign(size, 1000);

    // Basta que rodemos uma BFS de múltiplas fontes com todos os PVs adjacentes a CDs como fontes
    // Fila de Vértices
    queue<int> q;

    for(int source: sources){    
        // Distancia 
        dist[source] = 1;
        // Colocamos x na frente da fila
        q.push(source);
    }

    while(!q.empty()){
        // Processando o primeiro nó da fila. Chamaremos ele de "pv". Em seguida, o removemos da fila.
        int pv = q.front(); q.pop();
        // Visitando todos os nós adjacentes à "pv" 
        for(int viz: adj[pv]){
            // Se a distância desse nó à algum CD for maior do que a distância de pv + 1
            if(dist[pv] + 1 < dist[viz]){
                // Então a distância do CD até esse nó é a distância do CD até pv + 1
                dist[viz] = dist[pv] + 1;
                // Colocamos o nó adjacente na lista de PVs a serem processados
                q.push(viz);
            }
        }
    }
}

void Graph::CheckCycle(){
    // Para checar a existência de um ciclo, basta rodar a DFS a partir de todos os PVs adjacentes à CDs
    for(int source: sources){
        // Vamos zerar o vetor de cores
        color.assign(size, 0);
        Dfs(source);
    }
}

void Graph::Dfs(int x){
    // A cor 1 significa que x está na rota que estamos processando
    color[x] = 1;
    // Vamos agora olhar para todos os PVs adjacentes a x
    for(int pv: adj[x]){
        // Se esse PV está na mesma rota atual, encontramos um ciclo
        if(color[pv] == 1) hasCycle = true;
        // Se a cor for 0, significa que esse PV não foi processado em nenhuma rota ainda, iremos processá-lo
        if(color[pv] == 0) Dfs(pv);
    }
    // A cor -1 significa que o PV já foi processado em alguma rota
    color[x] = -1;
}