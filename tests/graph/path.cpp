#include "graph/path.hpp"
#include <iostream>

int main() {
  vector<vector<int>> adj, rev_adj;

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "graph") {
      int n, m;
      cin >> n >> m;
      if(!cin) break;
      adj.clear();
      adj.resize(n);
      rev_adj.clear();
      rev_adj.resize(n);
      for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if(!cin) break;
        a--, b--;
        adj[a].push_back(b);
        rev_adj[b].push_back(a);
      }
      if(!cin) break;

    } else if(op == "count") {
      int src;
      cin >> src;
      if(!cin) break;
      src--;

      auto result = count_paths(rev_adj, src);
      for(auto i: result) {
        cout << i << " ";
      }
      cout << endl;

    } else if(op == "longest") {
      int from, to;
      cin >> from >> to;
      if(!cin) break;
      from--, to--;

      auto result = longest_path(adj, from, to);
      if(result == nullopt) {
        cout << "nullopt" << endl;
      } else {
        for(auto i: *result) {
          cout << i + 1 << " ";
        }
        cout << endl;
      }
    }
  }
}
