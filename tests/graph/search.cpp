#include "graph/search.hpp"
#include <iostream>

int main() {
  vector<vector<int>> adj;
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
      for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if(!cin) break;
        a--, b--;
        adj[a].push_back(b);
      }
      if(!cin) break;

    } else if(!adj.empty()) {
      if(op == "bfs") {
        int root;
        cin >> root;
        if(!cin) break;
        root--;

        auto result = bfs(root, adj);
        for(bool i: result.is_vis) {
          cout << i << " ";
        }
        cout << endl;
        for(int i: result.parent) {
          cout << (i == -1 ? -1 : i + 1) << " ";
        }
        cout << endl;
        for(int i: result.dist) {
          cout << i << " ";
        }
        cout << endl;

      } else if(op == "dfs") {
        int root;
        cin >> root;
        if(!cin) break;
        root--;

        auto result = dfs(root, adj);
        for(bool i: result.is_vis) {
          cout << i << " ";
        }
        cout << endl;
        for(int i: result.parent) {
          cout << (i == -1 ? -1 : i + 1) << " ";
        }
        cout << endl;
        for(int i: result.depth) {
          cout << i << " ";
        }
        cout << endl;
        for(int i: result.size) {
          cout << i << " ";
        }
        cout << endl;
        for(int i: result.entry) {
          cout << i << " ";
        }
        cout << endl;
        for(int i: result.exit) {
          cout << i << " ";
        }
        cout << endl;
        for(int i: result.low) {
          cout << i << " ";
        }
        cout << endl;
        for(int i: result.pre_order) {
          cout << i + 1 << " ";
        }
        cout << endl;
        for(int i: result.post_order) {
          cout << i + 1 << " ";
        }
        cout << endl;
      }
    }
  }
}
