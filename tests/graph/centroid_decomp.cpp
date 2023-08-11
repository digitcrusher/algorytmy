#include "graph/centroid_decomp.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    auto result = centroid_decomp(adj);
    for(auto i: result.parent) {
      cout << (i == -1 ? -1 : i + 1) << " ";
    }
    cout << endl;
    for(int a = 0; a < n; a++) {
      for(auto b: result.children[a]) {
        cout << a + 1 << " " << b + 1 << endl;
      }
    }
  }
}
