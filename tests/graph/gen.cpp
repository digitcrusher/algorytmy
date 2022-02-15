#include "graph/gen.hpp"
#include <ctime>
#include <iostream>

int main() {
  bool is_directed = false;
  bool has_self_loops = false;
  bool has_multi_edges = false;
  bool is_connected = false;
  bool is_acyclic = false;
  int k_colorable = -1;

  while(true) {
    int n, m;
    cin >> n >> m;
    if(!cin) break;
    srand(time(nullptr));
    auto adj = gen_graph(
      n, m,
      is_directed, has_self_loops,
      has_multi_edges, is_connected,
      is_acyclic, k_colorable
    );

    for(int a = 0; a < n; a++) {
      for(int b: adj[a]) {
        if(!is_directed && a > b) continue;
        cout << a + 1 << " " << b + 1 << endl;
      }
    }

#ifdef DOT
    cout << (is_directed ? "digraph" : "graph") << " {\n";
    for(int i = 0; i < n; i++) {
      cout << "  " << i + 1 << ";\n";
    }
    for(int a = 0; a < n; a++) {
      for(int b: adj[a]) {
        if(!is_directed && a > b) continue;
        cout << "  " << a + 1 << (is_directed ? " -> " : " -- ") << b + 1 << ";\n";
      }
    }
    cout << "}\n";
#endif
  }
}
