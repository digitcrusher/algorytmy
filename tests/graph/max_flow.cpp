#include "graph/max_flow.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m, src, sink;
    cin >> n >> m >> src >> sink;
    src--, sink--;
    vector<vector<pair<int, ll>>> adj(n);
    for(int i = 0; i < m; i++) {
      int a, b;
      ll cap;
      cin >> a >> b >> cap;
      a--, b--;
      adj[a].push_back({b, cap});
    }

    auto result = max_flow(adj, src, sink);
    cout << result.global_flow << endl;
    cout << result.flow;
  }
}
