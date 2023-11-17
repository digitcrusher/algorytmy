#include "graph/cycle.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string type;
    cin >> type;
    if(type != "dir" && type != "undir") continue;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(auto i: v::iota(0, m)) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
      if(type == "undir") {
        adj[b].push_back(a);
      }
    }

    auto result = type == "dir" ? find_cycle_dir(adj) : find_cycle_undir(adj);
    if(result) {
      cout << (*result | v::transform(λ(_ + 1))) << endl;
    } else {
      cout << "nullopt" << endl;
    }
  }
}
