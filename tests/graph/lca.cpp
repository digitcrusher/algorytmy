#include "graph/lca.hpp"
#include "graph/binary_lift.hpp"
#include "graph/search.hpp"
#include <iostream>

int main() {
  int n, root;
  vector<vector<int>> adj;
  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "graph") {
      cin >> n >> root;
      if(!cin) break;
      root--;
      adj.clear();
      adj.resize(n);
      for(int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        if(!cin) break;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
      }
      if(!cin) break;

    } else if(op == "lca") {
      int a, b;
      cin >> a >> b;
      if(!cin) break;
      a--, b--;
      auto dfs = ::dfs(root, adj);
      int result = lca_lifting(binary_lift(dfs.parent), dfs.depth, a, b);
      cout << result + 1 << endl;
      assert(result == lca_rmq(adj, root, a, b));
    }
  }
}
