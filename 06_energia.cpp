#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
    friend class DFS_Paths;
  public:
    Graph(int VV, int EE) : V(VV), E(EE) {
        adjs = vector<vector<int> > (V);
    }
    
    int get_V() {return V;}
    
    int get_E() {return E;}
    
    void add_edge(int u, int v) {
        adjs[u].push_back(v);
        adjs[v].push_back(u);
    }
    
    vector<int> get_adjs(int u) {return adjs[u];}
    
    void print_adjs() {
        for(int u = 0; u < V; u++) {
            cout << u << ": ";
            for (int v : adjs[u])
                cout << v << ' ';
            cout << '\n';
        }
    }

  private:
    int V, E;
    vector<vector<int> > adjs;
};

class DFS_Paths {
  public:
    DFS_Paths(Graph *G, int ss) : s(ss) {
        marked = vector<bool> (G->V);
        edge_to = vector<int> (G->V);
        dfs(G, s);
    }

    bool has_path_to(int u) {return marked[u];}

    vector<int> path_to(int u) {
        if (!has_path_to(u)) return {};
        vector<int> path;
        for (int x = u; x != s; x = edge_to[x])
            path.push_back(x);
        reverse(path.begin(), path.end());
        return path;
    }

  private:
    int s;                 // Origem dos caminhos a computar
    vector<bool> marked;   // A DFS foi chamada neste vértice?
    vector<int> edge_to;   // edge_to[v]: quem descobriu v?

    void dfs(Graph *G, int u) {
        marked[u] = true;
        for (auto v : G->adjs[u]) {
            if (!marked[v]) {
                edge_to[v] = u;
                dfs(G, v);
            }
        }
    }

};

int main () {
    // Cria o grafo
    int V, E;
    cin >> V >> E;
    V--; E--;

    
