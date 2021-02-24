#include <bits/stdc++.h>
#include "mst.h"

using namespace std;

int main(){
    int nVertices, nArestas;
    cin >> nVertices >> nArestas;
    
    // Instanciando uma estrutura Disjoint Set Union
    MST mst(nVertices);

    // Lê a atratividade de cada vértice
    for(int &val: mst.value)
        cin >> val;

    // Lê as arestas
    for(int i = 0; i < nArestas; i++){
        int c, v1, v2;
        cin >> v1 >> v2 >> c;
        mst.AddEdge(c, v1, v2);
    }

    // Criando a AGM
    mst.Kruskal();

    // Imprimindo a saída
    // Custo e atratividade total
    cout << mst.mstCost << " " << mst.mstAtract << endl;
    // Participação de cada vértice na AGM
    for(int v: mst.inMst) cout << v << " ";
    cout << endl;
    // Arestas da AGM
    for(auto [v1, v2, w]: mst.mstEdges) cout << v1 << " " << v2 << " " << w << endl; 

    exit(0);
}
