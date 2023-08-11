#include "graph/bridges.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    auto [result, bccs] = bridges(adj);
    for(auto i: result.cut_vertices) {
      cout << i + 1 << endl;
    }
    for(auto [a, b]: result.bridges) {
      cout << a + 1 << " " << b + 1 << endl;
    }

    cout << endl;
    for(auto i: bccs.parent) {
      cout << i + 1 << " ";
    }
    cout << endl;
    for(int a = 0; a < n; a++) {
      if(bccs.parent[a] != a) {
        assert(bccs.adj[a].empty());
      }
      for(auto b: bccs.adj[a]) {
        if(a > b) continue;
        cout << a + 1 << " " << b + 1 << endl;
      }
    }
  }
}
