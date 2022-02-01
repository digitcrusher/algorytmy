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

  int n, m;
  cin >> n >> m;
  srand(time(nullptr));
  auto adj = gen_graph(
    n, m,
    is_directed, has_self_loops,
    has_multi_edges, is_connected,
    is_acyclic, k_colorable
  );

  cout << (is_directed ? "digraph" : "graph") << " {\n";
  for(int i = 0; i < n; i++) {
    cout << "  " << i + 1 << ";\n";
  }
  for(int i = 0; i < n; i++) {
    for(int j: adj[i]) {
      if(!is_directed && i > j) continue;
      cout << "  " << i + 1 << (is_directed ? " -> " : " -- ") << j + 1 << ";\n";
    }
  }
  cout << "}\n";
}
