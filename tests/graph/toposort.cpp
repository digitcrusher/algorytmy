#include "graph/toposort.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector in_deg(n, 0);
    for(auto i: v::iota(0, m)) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
      in_deg[b]++;
    }

    auto kahn = toposort_kahn(adj, in_deg);
    cout << (kahn | v::transform(λ(_ + 1))) << endl;

    auto dfs = toposort_dfs(adj);
    cout << (dfs | v::transform(λ(_ + 1))) << endl;
  }
}
