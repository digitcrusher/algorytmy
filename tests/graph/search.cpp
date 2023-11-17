#include "graph/search.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n, m, root;
    cin >> n >> m >> root;
    root--;
    vector<vector<int>> adj(n);
    for(auto i: v::iota(0, m)) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].push_back(b);
    }

    auto bfs = ::bfs(adj, root);
    cout << bfs.is_vis << endl;
    cout << (bfs.parent | v::transform(λ(_ == -1 ? -1 : _ + 1))) << endl;
    cout << bfs.dist << endl;

    cout << endl;
    auto dfs = ::dfs(adj, root);
    cout << dfs.is_vis << endl;
    cout << (dfs.parent | v::transform(λ(_ == -1 ? -1 : _ + 1))) << endl;
    cout << dfs.depth << endl;
    cout << dfs.size << endl;
    cout << dfs.entry << endl;
    cout << dfs.exit << endl;
    cout << dfs.low << endl;
    cout << (dfs.pre_order | v::transform(λ(_ + 1))) << endl;
    cout << (dfs.post_order | v::transform(λ(_ + 1))) << endl;
  }
}
