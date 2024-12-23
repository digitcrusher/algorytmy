#include "graph/gen.hpp"
#include "iostream.hpp"

int main() {
  auto is_directed = false;
  auto has_self_loops = false;
  auto has_multi_edges = false;
  auto is_connected = false;
  auto is_acyclic = false;
  int k_colorable = -1;

  while(cin) {
    int n, m;
    cin >> n >> m;
    srand(time(nullptr));
    auto adj = gen_graph(
      n, m,
      is_directed, has_self_loops,
      has_multi_edges, is_connected,
      is_acyclic, k_colorable
    );

    for(auto a: v::iota(0, n)) {
      for(auto b: adj[a] | v::filter(λ(is_directed || a <= _))) {
        cout << a + 1 << " " << b + 1 << endl;
      }
    }

#ifdef DOT
    cout << (is_directed ? "digraph" : "graph") << " {\n";
    for(auto i: v::iota(0, n)) {
      cout << "  " << i + 1 << ";\n";
    }
    for(auto a: v::iota(0, n)) {
      for(auto b: adj[a] | v::filter(λ(is_directed || a <= _))) {
        cout << "  " << a + 1 << (is_directed ? " -> " : " -- ") << b + 1 << ";\n";
      }
    }
    cout << "}\n";
#endif
  }
}
