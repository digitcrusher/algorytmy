#include "graph/bridges.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(auto i: v::iota(0, m)) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    auto [result, bccs] = bridges(adj);
    cout << (result.cut_vertices | v::transform(λ(_ + 1))) << endl;
    for(auto [a, b]: result.bridges) {
      cout << a + 1 << " " << b + 1 << endl;
    }

    cout << endl;
    cout << (bccs.parent | v::transform(λ(_ + 1))) << endl;
    for(auto a: v::iota(0, n)) {
      if(bccs.parent[a] != a) {
        assert(bccs.adj[a].empty());
      }
      for(auto b: bccs.adj[a] | v::filter(λ(a <= _))) {
        cout << a + 1 << " " << b + 1 << endl;
      }
    }
  }
}
