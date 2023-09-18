#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Graph {
    friend class BFS_Paths;
    friend class PropriedadesDoGrafo;
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
        
    private:
        int V, E;
        vector<vector<int> > adjs;
};

class BFS_Paths {
    friend class PropriedadesDoGrafo;
    public:
        BFS_Paths(Graph *G, int ss) : s(ss) {
            mk = vector<bool> (G->V);
            pai = vector<int> (G->V);
            d = vector<int> (G->V, -1);
            bfs(G, s);
        }        

        vector<int> min_path_to(int u) {
            vector<int> p;
            if (has_path_to(u)) {
                for (int x = u; x != s; x = pai[x]) {
                    p.push_back(x);
                }
                reverse(p.begin(), p.end());
            }
            return p;
        }

        bool has_path_to(int u) { 
            return mk[u]; 
        }

        int min_dist_to(int u) { 
            return d[u];
        }
    
    private:
        int s;           // origem
        vector<bool> mk; // vetor de maração
        vector<int> pai; // vetor de pais
        vector<int> d;   // vetor de distâncias

        void bfs(Graph *G, int s) {
            queue<int> q;
            d[s] = 0;
            mk[s] = true;
            q.push(s);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : G->adjs[u]) {
                    if (!mk[v]) {
                        d[v] = d[u] + 1;
                        pai[v] = u;
                        mk[v] = true;
                        q.push(v);
                    }
                }
            }
        }
};

class PropriedadesDoGrafo {
    public:
        PropriedadesDoGrafo(Graph *G) {
            exc = vector<int> (G->V); // vetor de excentricidades
            
            // Procurar todas as excentricidades do grafo em rodando os vértices
            for(int s = 0; s < G->V; s++) {
                // Salva no vetor a excentricidade do vetor
                exc[s] = excentricidade(G, s);
            }
            
        }
        
        // A excentricidade de um vértice u é o comprimento do menor caminho deste vértice até o vértice mais distante de u.
        int excentricidade(Graph *G, int s) {
            BFS_Paths *obj = new BFS_Paths(G, s);

            return *max_element(obj->d.begin(), obj->d.end());
        }

        // O diâmetro de um grafo é a excentricidade máxima de qualquer vértice deste grafo. 
        int diametro() {
            // Retorna o valor mais alto no vetor de excentricidades
            return *max_element(exc.begin(), exc.end());
        }


        // O raio de um grafo é a menor excentricidade de qualquer vértice deste grafo.
        int raio() {
            // Retorna o valor mais baixo no vetor de excentricidades
            return *min_element(exc.begin(), exc.end());
        }

        // Um centro é um vértice cuja excentricidade é exatamente o raio.
        int centro(Graph *G) {
            // Roda todos os vértices
            for(int s = 0; s < G->V; s++) {
                // Se a excentridade do vértice for igual ao raio retorna ele
                if (excentricidade(G, s) == raio()) {
                    return s;
                }
            }

            return -1;
        }

    private:
        vector<int> exc;
};


int main () {
    int V, E;
    cin >> V >> E;
    Graph* G = new Graph(V, E);
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        G->add_edge(u, v);
    }

    PropriedadesDoGrafo *prop = new PropriedadesDoGrafo(G);

    cout << "Diâmetro: " << prop->diametro() << '\n';
    cout << "Raio: "<< prop->raio() << '\n';
    cout << "Centro: Vértice "<< prop->centro(G) << '\n';

    delete G, prop;
    return 0;
}

    