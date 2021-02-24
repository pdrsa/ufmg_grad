#include <bits/stdc++.h>
using namespace std;

// Classe geradora de AGM. Implementada com Union Find.
class MST{
    public:
        // Construtor
        MST(int sz);
        // Adiciona uma aresta de v1 para v2 com peso W
        void AddEdge(int w, int v1, int v2);
        // Gera a AGM
        void Kruskal();
        // Vetor que guarda a atratividade de cada vértice
        vector<int> value;
        // Vetor com as arestas da AGM
        vector<tuple<int, int, int>> mstEdges;
        // Vetor com a quantidade de arestas na AGM com ligação a cada vértice
        vector<int> inMst;
        // Atratividade da AGM
        int mstAtract;
        // Custo da AGM
        int mstCost;
    protected:
        // Retorna o representante do conjunto de x
        int Find(int x);
        // Une os conjuntos de x e y (Retorna se x e y são de conjuntos diferentes)
        bool Union(int x, int y);
        // Vetor que guarda o representante do conjunto de cada elemento
        vector<int> comp;        
        // Vetor que guarda o tamanho do conjunto de cada elemento
        vector<int> size;
        // Vetor que guarda informações acerca das arestas do grafo
        vector<tuple<int, int, int, int>> edges;
};

MST::MST(int sz){
    comp  = value = inMst = vector<int> (sz);
    size  = vector<int> (sz, 1);
    // Inicializa cada elemento como pertencente ao seu próprio conjunto
    iota(comp.begin(), comp.end(), 0);
}

void MST::AddEdge(int w, int v1, int v2){
    // Guardamos a atratividade negada, assim, quando ordenarmos, a atratividade maior será priorizada
    edges.emplace_back(w, -value[v1] - value[v2], v1, v2);
}

// Find recursivo com path compression
int MST::Find(int x){
    return comp[x] = (comp[x] == x ? x : Find(comp[x]));
}

// Union com Small to Large
bool MST::Union(int x, int y){
    x = Find(x), y = Find(y);
    // Se pertencem ao mesmo conjunto
    if(x == y) return false;
    // x sempre é o menor conjunto
    if(size[x] > size[y]) swap(x, y);
    // Apontamos x pra y
    comp[x] = y;
    // Somamos o tamanho de x ao tamanho de y
    size[y] += size[x];
    // Se não pertenciam ao mesmo conjunto
    return true;
}

// Algoritmo de Kruskal para gerar a AGM
void MST::Kruskal(){
    // Zeramos a atratividade total e o custo total
    mstAtract = mstCost = 0;
    // Ordena as arestas
    sort(edges.begin(), edges.end());
    for(auto [w, at, v1, v2]: edges){
        // Se são de componentes diferentes
        if(Union(v1, v2)){
            // Adiciona aresta na AGM 
            mstEdges.emplace_back(v1, v2, w);
            // Soma à atratividade total e ao custo total
            mstAtract -= at, mstCost += w;
            // Adiciona mais um ao número de participações na AGM para v1 e v2
            inMst[v1]++, inMst[v2]++;
        }
    }
    
    // Ordenando para que a saída fique bem determinada
    sort(mstEdges.begin(), mstEdges.end());
}