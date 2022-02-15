#include "graph/two_color.hpp"
#include <iostream>

int main() {
  while(true) {
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
      adj[b].push_back(a);
    }
    if(!cin) break;

    auto result = two_color(adj);
    if(result == nullopt) {
      cout << "nullopt" << endl;
    } else {
      for(int i: *result) {
        cout << i << " ";
      }
      cout << endl;
    }
  }
}
