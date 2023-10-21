#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

class Edge {
  public:
    Edge(int uu, int vv, double ww) : u(uu), v(vv), w(ww) {}

    int ooutro(int vert) {
        if (vert == u) return v;
        return u;
    }

    int get_u() {return u;}
    int get_v() {return v;}
    double get_w() {return w;}

    bool operator< (const Edge& ee) const {return w > ee.w;}

    void print_edge() {
        cout << "(" << setw(2) << u << ","
                      << setw(2) << v << "," 
                      << setw(5) << w << ")\n";
    }
    //OU: friend ostream& operator<< (ostream& out, Edge& x);  // ANOTHER OPTION
  private:
    int u, v;
    double w;
};

class Grafo_com_pesos {
  public:
    Grafo_com_pesos(int VV, int EE) : V(VV), E(EE), adjs(VV) {}

    void add_edge(Edge e) {
        int u = e.get_u(), v = e.get_v();
        adjs[u].push_back(e);
        adjs[v].push_back(e);
    }

    vector<Edge> get_adjs(int u) {return adjs[u];}

    vector<Edge> get_edges() {
        vector<Edge> edges;
        for (int u = 0; u < V; u++) {
            for (auto ee : adjs[u]) {
                if (ee.ooutro(u) > u)   // só uma instância de cada edge
                    edges.push_back(ee);
            }
        }
        return edges;
    }

    int get_V() {return V;}
    int get_E() {return E;}
    void print_edges() {
        vector<Edge> edges = get_edges();
        for (auto ee : edges)
            ee.print_edge();
        cout << '\n';
    }
  private:
    const int V, E;
    vector<vector<Edge>> adjs;
};

class UF {
    vector<int> id;  // id de cada componente
    int c;           // nro de componentes
    vector<int> tam; // tamanho de cada componente como raiz

  public:
    UF(int N) : c(N), id(N), tam(N) {
        for (int i = 0; i < N; i++) {
            id[i] = i;
            tam[i] = 1; 
        }
    }

    int contagem() {return c;}
    bool conectados(int p, int q) {return find(p) == find(q);}

    int find(int p) {
        if (id[p] == p) return p;
        id[p] = find(id[p]);
        return id[p];
    }

    void join(int p, int q) {
        int raiz_p = find(p);
        int raiz_q = find(q);
        if (raiz_p == raiz_q) return;
        if (tam[raiz_p] < tam[raiz_q]) { 
            id[raiz_p] = raiz_q;  tam[raiz_q] += tam[raiz_p]; 
        }
        else {
            id[raiz_q] = raiz_p;  tam[raiz_p] += tam[raiz_q]; 
        }
        c--;
    }
};

class KruskalMST {
  public:
    KruskalMST(Grafo_com_pesos* G) : peso(0.) {
        // Inicializa a PQ de mín
        priority_queue<Edge> pq;  // PQ de max com "<" redefinido
        for (auto edge : G->get_edges())
            pq.push(edge);

        // Algoritmo Kruskal
        UF* uf = new UF(G->get_V());
        while (!pq.empty() and mst.size() < G->get_V()-1) {
            Edge e = pq.top();   pq.pop(); 
            int u = e.get_u(), v = e.get_v();  
            double w = e.get_w();

            if (uf->conectados(u, v)) continue; 
            (...)
        }
    }

    vector<Edge> get_edges() {...}
    double get_peso() {return peso;}
    void print_edges() {
        for (auto ee : mst)
            ee.print_edge();
        cout << '\n';
    }
  private:
    vector<Edge> mst;  // para coletar as arestas da MST
    double peso;       // peso da MST
};

/*******************
 * Cliente de teste
 *******************/
int main () {
    int V, E;
    cin >> V >> E;

    // Cria o grafo:
    Grafo_com_pesos *G = new Grafo_com_pesos(V, E);
    for (int i = 0; i < E; i++) {
        int u, v; double w;
        cin >> u >> v >> w;
        G->add_edge({u, v, w});
    }
    G->print_edges();
    
    // Cria um objeto do tipo KruskalMST
    KruskalMST* kmst = new KruskalMST(G);

    // Consulta kmst e imprime MST para este G
    (...)

    return 0;
}
