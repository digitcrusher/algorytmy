#include "graph/search.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m, root;
    cin >> n >> m >> root;
    root--;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
    }

    auto bfs = ::bfs(adj, root);
    cout << bfs.is_vis << endl;
    for(auto i: bfs.parent) {
      cout << (i == -1 ? -1 : i + 1) << " ";
    }
    cout << endl;
    cout << bfs.dist << endl;

    cout << endl;
    auto dfs = ::dfs(adj, root);
    cout << dfs.is_vis << endl;
    for(auto i: dfs.parent) {
      cout << (i == -1 ? -1 : i + 1) << " ";
    }
    cout << endl;
    cout << dfs.depth << endl;
    cout << dfs.size << endl;
    cout << dfs.entry << endl;
    cout << dfs.exit << endl;
    cout << dfs.low << endl;
    for(auto i: dfs.pre_order) {
      cout << i + 1 << " ";
    }
    cout << endl;
    for(auto i: dfs.post_order) {
      cout << i + 1 << " ";
    }
    cout << endl;
  }
}
