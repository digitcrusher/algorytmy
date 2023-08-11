#include "graph/min_cost_flow.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m, src, sink, desired_flow;
    cin >> n >> m >> src >> sink >> desired_flow;
    src--, sink--;
    vector<vector<Edge>> adj(n);
    for(int i = 0; i < m; i++) {
      int a, b, cap;
      ll cost;
      cin >> a >> b >> cap >> cost;
      a--, b--;
      adj[a].push_back({b, cap, cost});
    }

    auto result = min_cost_flow(adj, src, sink, desired_flow);
    cout << result.global_flow << " " << result.global_cost << endl;
    cout << result.flow;
  }
}
