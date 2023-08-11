#include "graph/eulerian_path.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string type;
    cin >> type;
    if(type != "dir" && type != "undir") continue;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
      if(type == "undir") {
        adj[b].push_back(a);
      }
    }

    auto result = type == "dir" ? eulerian_path_dir(adj) : eulerian_path_undir(adj);
    if(result) {
      for(auto i: *result) {
        cout << i + 1 << " ";
      }
      cout << endl;
    } else {
      cout << "nullopt" << endl;
    }
  }
}
