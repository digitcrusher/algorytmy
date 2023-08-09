#include "graph/min_cost_flow.hpp"
#include <iostream>

int main() {
  while(true) {
    int n, m, src, sink, desired_flow;
    cin >> n >> m >> src >> sink >> desired_flow;
    if(!cin) break;
    src--, sink--;
    vector<vector<Edge>> adj(n);
    for(int i = 0; i < m; i++) {
      int a, b, cap;
      ll cost;
      cin >> a >> b >> cap >> cost;
      if(!cin) break;
      a--, b--;
      adj[a].push_back({b, cap, cost});
    }
    if(!cin) break;

    auto [flow, global_flow, global_cost] = min_cost_flow(adj, src, sink, desired_flow);
    for(auto &row: flow) {
      for(auto cell: row) {
        cout << cell << " ";
      }
      cout << endl;
    }
    cout << global_flow << " " << global_cost << endl;
  }
}
