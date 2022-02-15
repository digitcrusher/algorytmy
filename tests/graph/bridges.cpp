#include "graph/bridges.hpp"
#include <iostream>

int main() {
  while(true) {
    int n, m;
    cin >> n >> m;
    if(!cin) break;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      if(!cin) break;
      a--, b--;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    if(!cin) break;

    auto result = bridges(adj);
    for(int i: result.cut_vertices) {
      cout << i + 1 << endl;
    }
    for(auto [a, b]: result.bridges) {
      cout << a + 1 << " " << b + 1 << endl;
    }
  }
}
