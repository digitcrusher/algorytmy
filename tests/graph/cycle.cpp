#include "graph/cycle.hpp"
#include <iostream>

int main() {
  while(true) {
    string type;
    cin >> type;
    if(!cin) break;

    if(type != "dir" && type != "undir") continue;
    int n, m;
    cin >> n >> m;
    if(!cin) break;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      if(!cin) break;
      a--, b--;
      adj[a].push_back(b);
      if(type == "undir") {
        adj[b].push_back(a);
      }
    }
    if(!cin) break;

    auto result = type == "dir" ? find_cycle_dir(adj) : find_cycle_undir(adj);
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
