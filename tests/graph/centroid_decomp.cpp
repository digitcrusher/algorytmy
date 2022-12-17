#include "graph/centroid_decomp.hpp"
#include <iostream>

int main() {
  while(true) {
    int n;
    cin >> n;
    if(!cin) break;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
      int a, b;
      cin >> a >> b;
      if(!cin) break;
      a--, b--;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    if(!cin) break;

    auto result = centroid_decomp(adj);
    for(int i: result.parent) {
      cout << (i == -1 ? -1 : i + 1) << " ";
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
      for(int j: result.children[i]) {
        cout << i + 1 << " " << j + 1 << endl;
      }
    }
  }
}
