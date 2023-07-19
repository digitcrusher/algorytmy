#include "graph/flow.hpp"
#include <iostream>

int main() {
  while(true) {
    int n, m, src, sink;
    cin >> n >> m >> src >> sink;
    if(!cin) break;
    src--, sink--;
    vector<vector<pair<int, ll>>> adj(n);
    for(int i = 0; i < m; i++) {
      int a, b;
      ll cap;
      cin >> a >> b >> cap;
      if(!cin) break;
      a--, b--;
      adj[a].push_back({b, cap});
    }
    if(!cin) break;

    auto [flow, global_flow] = max_flow(adj, src, sink);
    for(auto &row: flow) {
      for(auto cell: row) {
        cout << cell << " ";
      }
      cout << endl;
    }
    cout << global_flow << endl;
  }
}
