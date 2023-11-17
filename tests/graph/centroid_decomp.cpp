#include "graph/centroid_decomp.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(auto i: v::iota(0, n - 1)) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    auto result = centroid_decomp(adj);
    cout << (result.parent | v::transform(λ(_ == -1 ? -1 : _ + 1))) << endl;
    for(auto a: v::iota(0, n)) {
      for(auto b: result.children[a]) {
        cout << a + 1 << " " << b + 1 << endl;
      }
    }
  }
}
