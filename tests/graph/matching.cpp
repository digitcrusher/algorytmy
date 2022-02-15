#include "graph/matching.hpp"
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

    auto color = two_color(adj);
    if(color == nullopt) {
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
    for(int i = 0; i < n; i++) {
      if(result.pair[i] == -1 || i > result.pair[i]) continue;
      cout << i + 1 << " " << result.pair[i] + 1 << endl;
      assert(result.pair[result.pair[i]] == i);
    }
  }
}
