#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> id;

typedef pair<double, pair<int, int>> estrada;

int find(int p) {
    if(id[p] == p) return p;
    id[p] = find(id[p]);
    return id[p];
}

void join(int p, int q) { // quick-union
    int id_p = find(p);
    int id_q = find(q);
    id[id_p] = id_q;
}

double mst(vector<estrada>& E) {
    sort(E.begin(), E.end());
    for (int i = 0; i < N; i++) {
        id[i] = i;
    }

    // Executando Kruskal e computando o custo mínimo
    int j = 0; // Contador de arestas totais
    int k = 0; // Contador de arestas inseridas
    double res = 0.0;
    while (k < N-1 and j < M) {
        double u = E[j].first;
        int p = E[j].second.first;
        int q = E[j].second.second;

        // AQUI ESTÁ O UNION-FIND
        if(find(p) != find(q)) {
            join(p, q);
            res += u;
        }
        j++;
    }
    return res;
}

int main() {
    cin >> N >> M;

    id = vector<int> (N);
    vector<estrada> E (M);

    for (int j = 0; j < M; j++) {
        int p, q; double u;
        cin >> p >> q >> u;
        cout << p << ' ' << q << ' ' << u << '\n';
        E[j] = {u, {p, q}};
    }

    // Kruskal
    cout << mst(E) << '\n';

    return 0;
}