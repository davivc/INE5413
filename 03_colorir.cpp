#include <iostream>
#include <vector>

using namespace std;

// DFS matrix
vector<vector<bool> > g;

// Matrix size vars
int n, m;

// Final answer
int q;

// Adjacencies
vector<int> di = { -1, -1, -1,  0,  0, +1, +1, +1};
vector<int> dj = { -1,  0, +1, -1, +1, -1,  0, +1};

bool in (int i, int j) {
  return i >= 0 and i < n and j >= 0 and j < m; 
}

void floodfill(int iu, int ju) {
  g[iu][ju] = true; // Mark the box as read
  q++; // Update the answer

  // Look the adjacencies
  for (int t = 0; t < 8 ; t++) {
    int iv = iu + di[t], jv = ju + dj[t];
    if (in(iv, jv) and !g[iv][jv]) {
      floodfill(iv, jv);
    }
  }

}

int main() {
  // Data reading
  int x, y, k;
  cin >> n >> m >> x >> y >> k;
  // The starting coordinates don't start at zero so we need to fix that
  x--; y--;

  // Matrix resizing
  g = vector<vector<bool> > (n, vector<bool> (m, false));

  // Reading the marked boxes
  for (int i = 0; i < k; i++) {
    int a, b;
    cin >> a >> b;
    // The marked coordinates don't start at zero so we need to fix that
    a--; b--;
    g[a][b] = true;
  }

  // Floodfill (DFS)
  q = 0;
  floodfill(x, y);

  // Print result (the number of painted boxes)
  cout << q << '\n';

  return 0;
}