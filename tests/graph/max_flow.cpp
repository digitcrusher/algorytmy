#include "graph/max_flow.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m, src, sink;
    cin >> n >> m >> src >> sink;
    src--, sink--;
    vector<vector<pair<int, ll>>> adj(n);
    for(auto i: v::iota(0, m)) {
      int a, b;
      ll cap;
      cin >> a >> b >> cap;
      a--, b--;
      adj[a].emplace_back(b, cap);
    }

    auto result = max_flow(adj, src, sink);
    cout << result.global_flow << endl;
    cout << result.flow;
  }
}
