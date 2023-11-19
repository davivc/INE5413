// OBI2023 frete ic unicamp


#include<iostream>
#include<vector>
#include<queue>

#define INF 1e9

using namespace std;
typedef pair <int, int> pii;
vector<int> dist;
vector<vector<pii>> adjs;
priority_queue<pii, vector<pii>, greater<pii>> pq; // PQ de min

void relax(int u, int v, int weight) {
    if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.push({dist[v], v});
    }
}

void dijkstra() {
    pq.push({0, 0});

    while(!pq.empty()) {
        auto t = pq.top(); pq.pop();
        int d = t.first, u = t.second;

        if (d == dist[u]) {
            for (auto e : adjs[u]) {
                int v = e.first, weight = e.second;
                relax(u, v, weight);
            }
        }
    }
}

int main() {
    // Lendo os dados
    int V, E;
    cin >> V >> E;
    adjs = vector<vector<int>> (V);
    for (int j = 0; j < E; j++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adjs[a].push_back({b, c});
        adjs[b].push_back({a, c});
    }

    // Dijkstra
    dist = vector<int> (V, INF);
    dist[0] = 0;
    dijkstra();

    // Resultado
    cout << dist[V-1] << '\n';
}