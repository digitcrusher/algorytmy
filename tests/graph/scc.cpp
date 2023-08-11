#include "graph/scc.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n), rev_adj(n);
    for(int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
      rev_adj[b].push_back(a);
    }

    auto result = scc_kosaraju(adj, rev_adj);
    cout << result.scc_cnt << endl;
    for(auto i: result.node_scc) {
      cout << i + 1 << " ";
    }
    cout << endl;
    for(int a = 0; a < result.scc_cnt; a++) {
      for(auto b: result.scc_adj[a]) {
        cout << a + 1 << " " << b + 1 << endl;
      }
    }
  }
}
