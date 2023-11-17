#include "graph/lca.hpp"
#include "graph/binary_lift.hpp"
#include "graph/search.hpp"
#include "iostream.hpp"

int main() {
  int n, root;
  cin >> n >> root;
  root--;
  vector<vector<int>> adj(n);
  for(auto i: v::iota(0, n - 1)) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  auto dfs = ::dfs(adj, root);
  auto lift = binary_lift(dfs.parent);
  auto worse_lift = worse_binary_lift(dfs.parent);

  while(cin) {
    int a, b;
    cin >> a >> b;
    a--, b--;

    auto result = lca_lifting(dfs.parent, lift, dfs.depth, a, b);
    cout << result + 1 << endl;
    assert(result == lca_worse_lifting(worse_lift, dfs.depth, a, b));
    assert(result == lca_rmq(adj, root, a, b));
  }
}
