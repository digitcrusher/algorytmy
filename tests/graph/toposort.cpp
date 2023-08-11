#include "graph/toposort.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> in_deg(n, 0);
    for(int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
      in_deg[b]++;
    }

    auto kahn = toposort_kahn(adj, in_deg);
    for(auto i: kahn) {
      cout << i + 1 << " ";
    }
    cout << endl;

    auto dfs = toposort_dfs(adj);
    for(auto i: dfs) {
      cout << i + 1 << " ";
    }
    cout << endl;
  }
}
