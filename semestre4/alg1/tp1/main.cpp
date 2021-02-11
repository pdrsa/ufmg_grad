#include <bits/stdc++.h>
#include "graph.h"

using namespace std;

int main(){
    // Lendo a primeira linha
    string input;
    getline(cin, input);
    istringstream is(input);
    int nCds, nPvs;
	float tempDrop;
    is >> nCds; is >> nPvs; is >> tempDrop;

    // Construimos o grafo com as rotas
    Graph rotas(nPvs);

    for(int i = 0; i < nCds; i++){
        getline(cin, input);
        istringstream iss(input);
        int num;
        while(iss >> num){
            // Subtraímos 1 pois queremos que nosso grafo seja 0-based
            rotas.AddSource(num - 1);
        }
    }

    for(int i = 0; i < nPvs; i++){
        getline(cin, input);
        istringstream iss(input);
        int num;
        while(iss >> num){
            // Novamente, subtraímos 1 pois queremos que nosso grafo seja 0-based
            rotas.AddEdge(i, num-1);
        }
    }

    // Calculando Distâncias
    rotas.CalcDist();
    // Checando existência de Ciclos
    rotas.CheckCycle();

    // Conjunto de PVs alcançáveis
    set<int> pvsAlc;
    for(int i = 0; i < nPvs; i++){
        if(float(rotas.dist[i] * tempDrop) <= 30.0){
            pvsAlc.insert(i+1);
        }
    }

    // Imprimimos quantos PVs alcançamos
    cout << pvsAlc.size() << endl;
    // Se não alcançamos nenhum, imprimimos um asterisco
    if(pvsAlc.size() == 0)
        cout << '*' << endl;
    // Caso contrário, imprimimos tos que alcançamos
    else{
        for(int pv: pvsAlc)
            cout << pv << " ";
        cout << endl;
    }

    // Por fim, imprimimos se existe um ciclo no grafo
    cout << rotas.hasCycle << endl;
    exit(0);
}
