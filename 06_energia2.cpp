#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int> > adjs;
vector<bool> mk;

void bfs(int s) {
    queue<int> q;
    q.push(s);
    mk[s] = true;

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adjs[u]) {
            if(!mk[v]) {
                q.push(v);
                mk[v] = true;
            }
        }
    }
}

int main () {
    int E, L, k = 1;
    while (cin >> E >> L, E != 0) {
        adjs = vector<vector<int> > (E);
        for (int i = 0; i < L; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adjs[u].push_back(v);
            adjs[v].push_back(u);
        }
        mk = vector<bool> (E, false);
        bfs(0);

        // Result
        bool fail = false;
        for (int j = 0; j < E; j++) {
            if (mk[j] == false)
                fail = true;
        }

        cout << "Teste " << k++ << "\n";
        if (fail) cout << "falha\n\n";
        else cout << "normal\n\n";

    }
}