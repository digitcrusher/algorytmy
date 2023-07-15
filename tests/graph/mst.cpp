#include "graph/mst.hpp"
#include <iostream>

int main() {
  while(true) {
    int n, m;
    cin >> n >> m;
    if(!cin) break;
    vector<Edge> edges(m);
    vector<vector<Edge>> incident(n);
    vector<vector<pair<int, int>>> adj(n);
    for(auto &[a, b, cost]: edges) {
      cin >> a >> b >> cost;
      if(!cin) break;
      a--, b--;
      incident[a].push_back({a, b, cost});
      incident[b].push_back({a, b, cost});
      adj[a].push_back({b, cost});
      adj[b].push_back({a, cost});
    }
    if(!cin) break;

    auto kruskal = mst_kruskal(n, edges);
    cout << kruskal.cost << endl;
    for(auto [a, b, cost]: kruskal.edges) {
      cout << a + 1 << " " << b + 1 << " " << cost << endl;
    }
    auto prim = mst_prim(incident);
    cout << prim.cost << endl;
    for(auto [a, b, cost]: prim.edges) {
      cout << a + 1 << " " << b + 1 << " " << cost << endl;
    }
    auto prim2 = mst_prim(adj);
    cout << prim2.cost << endl;
    for(auto [a, b, cost]: prim2.edges) {
      cout << a + 1 << " " << b + 1 << " " << cost << endl;
    }
    assert(kruskal.cost == prim.cost && kruskal.cost == prim2.cost);
  }
}
