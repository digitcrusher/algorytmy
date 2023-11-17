#include "graph/scc.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n), rev_adj(n);
    for(auto i: v::iota(0, m)) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
      rev_adj[b].push_back(a);
    }

    auto result = scc_kosaraju(adj, rev_adj);
    cout << result.scc_cnt << endl;
    cout << (result.node_scc | v::transform(λ(_ + 1))) << endl;
    for(auto a: v::iota(0, result.scc_cnt)) {
      for(auto b: result.scc_adj[a]) {
        cout << a + 1 << " " << b + 1 << endl;
      }
    }
  }
}
