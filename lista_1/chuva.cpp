#include <iostream>
#include <vector>

using namespace std;

// DFS matriz de marcação
vector<vector<bool> > g;
// Parede de string pra mapear o ponto
vector<vector<string> > w;

// Tamanho da matriz
int n, m;

// Resposta final de pontos molhados
int q;

// Adjacências do ponto analisado
vector<int> di = { -1, -1, -1,  0,  0, +1, +1, +1};
vector<int> dj = { -1,  0, +1, -1, +1, -1,  0, +1};

// Limites
bool in (int i, int j) {
    return i >= 0 and i < n and j >= 0 and j < m; 
}

// Função de floodfill
void floodfill(int iu, int ju) {
    g[iu][ju] = true; // Mark o ponto como lido

    // Analisa as adjcências do ponto dado
    for (int t = 0; t < 8 ; t++) {
        int iv = iu + di[t], jv = ju + dj[t];
        // Só avança se :
        // - estiver dentro dos limites; 
        // - se não foi analisado ainda;
        // - se é um ponto permitido ("o" é ponto molhado e "#" é prateleira)
        
        if (in(iv, jv) and !g[iv][jv] and w[iv][jv] == ".") {
            // Avalia as regras estabelecidas para pintura do ponto molhado para poder marcar
            if (
                (in(iv+1, jv+1) and w[iv][jv+1] == "o" and w[iv+1][jv+1] == "#") ||                     // verifica se limites existem e w(i,j+1)= "o" e w(i+1,j+1)= "#"
                (in(iv, jv-1) and in(iv+1, jv-1) and w[iv][jv-1] == "o" and w[iv+1][jv-1] == "#") ||    // verifica se limites existem e w(i,j-1)= "o" e w(i+1,j-1)= "#"
                (in(iv-1, jv) and w[iv-1][jv] == "o"))                                                  // verifica se limites existem e w(i-1,j)= "o"
            {
                w[iv][jv] = "o";
                g[iv][jv] = true;
                floodfill(iv, jv);
            }
        }
    }
}

int main() {
    // Ler entradas
    int x, y;
    cin >> n >> m;

    // Matrix de marcação
    g = vector<vector<bool> > (n, vector<bool> (m, false));

    // Parede final
    w = vector<vector<string> > (n, vector<string> (m));

    // Leitura da parede
    for (int i = 0; i < n; i++) {
        string a;
        cin >> a;
        for (int j = 0; j < m; j++) {
            w[i][j] = a[j];

            // Marcar origem
            if (w[i][j] == "o") {
                x = i;
                y = j;
            }
        }
    }

    // Floodfill (DFS)
    q = 0;
    floodfill(x, y);

    // Avalia a parede
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // cout << w[i][j];
            if (w[i][j] == "o") {
                q++;
            }
        }
        // cout << '\n';

    }
    // cout << '\n';

    // Printa o número de pontos molhados
    cout << q << '\n';

    return 0;
}