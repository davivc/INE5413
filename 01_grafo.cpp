#include<iostream>
#include<vector>

using namespace std;

class Graph {
  public:
    Graph(int VV, int EE) : V(VV) , E(EE) {
        adjs = vector<vector<int> > (V);
        dfsMarked = vector<bool > (V, false);
        dfsEdgeTo = vector<int > (V);
    }

    void add_edge(int u, int v) {
        adjs[u].push_back(v);
        adjs[v].push_back(u);
    }
    
    int get_V() { return V; }                          // Informa nro de vértices deste grafo
    
    int get_E() { return E; }    
                          // Informa nro de arestas deste grafo
    vector<int> get_adjs(int u) { return adjs[u]; }    // Informa os vértices adjacentes a u dado
    
    void imprime() {
        for(int u = 0; u < V; u++) {
            cout << u << ": ";
            for (int v : adjs[u])
                cout << v << ' ';
            cout << '\n';
        }
    }

    bool check_dfs(int v) {
        if (dfsMarked[v] == true) { return true; }
        else { return false; }
    }

    void dfs(int v) {
        dfsMarked[v] = true;
        vector<int> v_adjs = get_adjs(v);

        for(int i = 0; i < v_adjs.size(); i++) {
            if(check_dfs(v_adjs[i]) == false) {
                dfsEdgeTo[v_adjs[i]] = v;
                dfs(v_adjs[i]);
            }
        }
    }

    void print_dfs() {
        for(int u = 0; u < V; u++) {
            cout << u << ": " << dfsMarked[u] <<  " - " << dfsEdgeTo[u];
            cout << '\n';
        }
    }

  private:
    int V, E;                       // Nro de vértices e de arestas
    vector<vector<int>> adjs;       // Lista de adjacências
    vector<bool> dfsMarked;
    vector<int> dfsEdgeTo;
};

int main() {
    int V, E;
    cin >> V >> E;
    Graph* G = new Graph(V, E);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        G->add_edge(u, v);
    }

    G->imprime();
    G->dfs(3);
    G->print_dfs();

    return 0;
}
