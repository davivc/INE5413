#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define INF 1000000001
typedef pair<double, int> pdi;
vector<double> dist;
vector<vector<pdi> > adjs;

void bellmanford(int s, int V) {
    dist.assign(V, INF);
    dist[s] = 0.;
    
    for (int i = 0; i < V-1; i++) { // V-1 vezes
        for (int u = 0; u < V; u++) { // all edges
            for (auto e : adjs[u]) {
                double weight = e.first;
                int v = e.second;
                dist[v] = min(dist[v], dist[u] + weight);
            }
        }
    }
}

bool temCicloNegativo(int V) {
    bool p = false; // não tem ciclo negativo
    for (int u = 0; u < V; u++) {
        for (auto e : adjs[u]) {
            double weight = e.first;
            int v = e.second;
            if (dist[v] > dist[u] + weight)
                return true;
        }
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    // Lendo dados
    adjs.assign(V, vector<pdi> ());
    for (int j = 0; j < E; j++) {
        int u, v; double weight;
        cin >> u >> v >> weight;
        adjs[u].push_back({weight, v});
    }

    bellmanford(0, V);
    
    // Resultados
    for (int u = 0; u < V; u++)
        cout << dist[u] << ' ';
    
    cout << '\n';
 
    return 0;
}
