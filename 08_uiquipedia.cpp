#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> d;
vector<bool> mk;
vector<vector<int>> adjs;

int main() {
    int n;
    cin >> n;

    // Inicializando
    mk = vector<bool> (2 * n, false);
    d = vector<int> (2 * n);

    adjs = vector<vector<int>> (2 * n);

    // Lendo os links diretos
    map<string, int> ind;
    int nc = 0;
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        if (ind.count(x) == 0) { // se x não existe no map
            ind[x] = nc++;
        }

        string y;
        cin >> y;
        if (ind.count(y) == 0) { // se y não existe no map
            ind[y] = nc++;
        }

        adjs[ind[x]].push_back(ind[y]);
    }

    // Adicionando os links da ordem alfabética ( o map já mantém tudo em ordem)
    int ix = -1; // ind's começam em 0
    for (auto p : ind) {
        int iy = p.second;
        if (ix != -1) {
            adjs[ix].push_back(iy);
            adjs[iy].push_back(ix);
        }
        ix = iy;
    }

    // Processando a query
    string p, a;
    cin >> p >> a;
    cout << bfs(ind[p], ind[a]) << '\n';


    // Map Output 
    for (auto p: ind) {
        cout << p.first << " -> " << p.second << '\n';
    }

    return 0;
}