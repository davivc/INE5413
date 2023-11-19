#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adjs, adjsR;
vector<bool> mk, mkR;
vector<int> id;
vector<int> posOrdemR;
int cont;

void dfsR(int u) {
    mkR[u] = true;
    for (int v : adjsR[u]) {
        if (!mkR[v])
            dfsR(v);
    }
    posOrdemR.push_back(u);
}

void dfs(int u) {
    mk[u] = true;
    id[u] = cont;
    for (int v : adjs[u]) {
        if (!mk[v])
            dfs(v);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        // Cria o digrafo e o reverso
        adjs.clear(); adjs.resize(n);
        adjsR.clear(); adjsR.resize(n);

        for (int j = 0; j < m; j++) {
            int x, y;
            cin >> x >> y; x--; y--;
            adjs[x].push_back(y);
            adjsR[y].push_back(x);
        }


        // Kosaraju
        // 1) DFS sobre GR (grafo reversa) para computar pós-ordem reversa
        posOrdemR.clear();
        // mkR = vector<bool> (n, false);
        mkR.assign (n, false);

        for (int s = 0; s < n ; s++) {
            if (!mkR[s])
                dfsR(s);
        }

        vector<int> posOrdermRrev (posOrdemR);
        reverse(posOrdermRrev.begin(), posOrdermRrev.end());

        // 2) DFS (normal) sobre G
        cont = 0;
        mk.assign (n, false);
        for (int s : posOrdemR) {
            if (!mk[s]) {
                dfs(s);
                cont++;
            }
        }

        // Resultado

        // 1) Coletando componentes fortemente conexas
        vector<vector<int>> comps(cont);
        for (int u = 0; u < n; u++) {
            comps[id[u]].push_back(u);
        }

        // 2) Contando componentes fortemente conexas sem aresta chegando de fora
        int cfcSem = 0;
        for (int k = 0; k < cont; k++) {
            bool sem = true;
            for (int uk : comps[k]) {
                for (int vk : adjsR[uk]) {
                    if (id[vk] != id[uk]) {
                        sem = false;
                        break;
                    }
                }
                if (!sem)
                    break;
            }
            if (sem)
                cfcSem++;
        }

        // 3) Imprimindo o resultado
        cout << cfcSem << '\n';
    }

    return 0;
}