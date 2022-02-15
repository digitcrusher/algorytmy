#include "graph/toposort.hpp"
#include <iostream>

int main() {
  while(true) {
    int n, m;
    cin >> n >> m;
    if(!cin) break;
    vector<vector<int>> adj(n);
    vector<int> in_deg(n, 0);
    for(int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      if(!cin) break;
      a--, b--;
      adj[a].push_back(b);
      in_deg[b]++;
    }
    if(!cin) break;

    auto kahn = toposort_kahn(adj, in_deg);
    for(int i: kahn) {
      cout << i + 1 << " ";
    }
    cout << endl;
    auto dfs = toposort_dfs(adj);
    for(int i: dfs) {
      cout << i + 1 << " ";
    }
    cout << endl;
  }
}
