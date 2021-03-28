#include <bits/stdc++.h>

using namespace std;

int n, d, t;

vector<int> discounts, times, prices;
vector<vector<double>> dp;

// Função que retorna (1-per) * value
double percent(int value, int per){
    double p = double(per)/100;
    p = 1-p;
    return double(value * p);
}

// Função recursiva. Recebe em qual posição estamos no processamento das escalas, 
// em qual posição estamos no desconto progressivo e quanto tempo já se passou.
double solve(int pos_i, int dis_j, int time_now){
    // Se for o estado final, retorne 0
    if(pos_i == n) return 0.0;
    // Se já tivermos atingido esse estado, retornamos o que guardamos
    if(dp[pos_i][dis_j] != -1) 
        return dp[pos_i][dis_j];
    // Esperamos até o tempo acabar e os descontos recomeçarem
    double a = solve(pos_i+1, 0, 0);
    double b = a;
    // Se não estivermos no último desconto e ainda tivermos tempo, pegamos o próximo desconto
    if (dis_j+1 < d and time_now + times[pos_i] < t)
        b = solve(pos_i+1, dis_j+1, time_now + times[pos_i]);
    
    // Decidimos qual das duas decisões é mais vantajosa e memorizamos
    return dp[pos_i][dis_j] = min(a, b) + percent(prices[pos_i], discounts[dis_j]);
}

int main(){
    // Primeiramente lemos n, d e t
    cin >> n >> d >> t;
    discounts = vector<int>(d);
    times = prices = vector<int> (n);
    dp = vector<vector<double>> (n, vector<double> (d, -1));
    

    // Lemos todos os descontos e somamos seus valores
    cin >> discounts[0];
    for(int i = 1; i < d; i++){
        cin >> discounts[i];
        discounts[i] += discounts[i-1];
    }
    
    // Lemos os tempos e preços
    for(int i = 0; i < n; i++)
        cin >> times[i] >> prices[i];

    // Duas casas de precisão
    cout << fixed << setprecision(2);
    // Chamamos a função recursiva que faz uso de programação dinâmica para encontrar a resposta
    cout << solve(0, 0, 0) << endl;
}