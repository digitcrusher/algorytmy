#include "graph/path.hpp"
#include <iostream>

int main() {
  vector<vector<int>> adj, rev_adj;

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "dag") {
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

    } else if(op == "tree") {
      int n;
      cin >> n;
      if(!cin) break;
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

    } else if(op == "count_paths_dag") {
      int src;
      cin >> src;
      if(!cin) break;
      src--;

      auto result = count_paths_dag(rev_adj, src);
      for(auto i: result) {
        cout << i << " ";
      }
      cout << endl;

    } else if(op == "longest_path_dag") {
      int from, to;
      cin >> from >> to;
      if(!cin) break;
      from--, to--;

      auto result = longest_path_dag(adj, from, to);
      if(result == nullopt) {
        cout << "nullopt" << endl;
      } else {
        for(auto i: *result) {
          cout << i + 1 << " ";
        }
        cout << endl;
      }

    } else if(op == "max_dist_tree") {
      auto [max_dist, a, b] = max_dist_tree(adj);
      for(auto i: max_dist) {
        cout << i << " ";
      }
      cout << endl;
      cout << a << " " << b << endl;
    }
  }
}
