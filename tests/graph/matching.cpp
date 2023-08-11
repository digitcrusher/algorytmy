#include "graph/matching.hpp"
#include "graph/two_color.hpp"
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

    auto color = two_color(adj);
    if(!color) {
      cout << "nullopt" << endl;
      continue;
    }
    vector<int> as, bs;
    for(int i = 0; i < n; i++) {
      if((*color)[i] == 1) {
        as.push_back(i);
      } else if((*color)[i] == 2) {
        bs.push_back(i);
      } else {
        assert(false);
      }
    }

    auto result = match_hopcroft_karp(adj, as, bs);
    cout << result.pairc << endl;
    for(int a = 0; a < n; a++) {
      auto b = result.pair[a];
      if(b == -1 || a > b) continue;
      cout << a + 1 << " " << b + 1 << endl;
      assert(a == result.pair[b]);
    }
  }
}
