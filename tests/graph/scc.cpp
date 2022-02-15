#include "graph/scc.hpp"
#include <iostream>

int main() {
  while(true) {
    int n, m;
    cin >> n >> m;
    if(!cin) break;
    vector<vector<int>> adj(n), rev_adj(n);
    for(int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      if(!cin) break;
      a--, b--;
      adj[a].push_back(b);
      rev_adj[b].push_back(a);
    }
    if(!cin) break;

    auto result = scc_kosaraju(adj, rev_adj);
    cout << result.scc_cnt << endl;
    for(int i = 0; i < n; i++) {
      cout << result.node_scc[i] + 1 << " ";
    }
    cout << endl;
    for(int a = 0; a < result.scc_cnt; a++) {
      for(int b: result.scc_adj[a]) {
        cout << a + 1 << " " << b + 1 << endl;
      }
    }
  }
}
