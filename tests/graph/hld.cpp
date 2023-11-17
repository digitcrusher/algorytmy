#include "graph/hld.hpp"
#include "ds/fenwick_tree/range_range.hpp"
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

  HLD hld(adj, root);

  vector<ll> init(n);
  for(auto i: v::iota(0, n)) {
    cin >> init[hld.node(i)];
  }

  struct ApplyChange {
    ll operator()(ll val, ll change, int elemc) {
      return val + change * elemc;
    }
  };
  FenwickTreeRangeRange<ll, plus<>, minus<>, ll, ApplyChange, plus<>, negate<>> tree(init, 0);

  while(cin) {
    string op;
    cin >> op;

    if(op == "get_node") {
      int node;
      cin >> node;
      node--;

      auto idx = hld.node(node);
      cout << tree.get(idx, idx) << endl;

    } else if(op == "modify_node") {
      int node;
      ll change;
      cin >> node >> change;
      node--;

      auto idx = hld.node(node);
      tree.modify(idx, idx, change);

    } else if(op == "get_path") {
      int a, b;
      cin >> a >> b;
      a--, b--;

      ll result = 0;
      for(auto [a, b]: hld.path(a, b)) {
        result = tree.values.add(result, tree.get(a, b));
      }
      cout << result << endl;

    } else if(op == "modify_path") {
      int a, b;
      ll change;
      cin >> a >> b >> change;
      a--, b--;

      for(auto [a, b]: hld.path(a, b)) {
        tree.modify(a, b, change);
      }

    } else if(op == "get_subtree") {
      int node;
      cin >> node;
      node--;

      auto [a, b] = hld.subtree(node);
      cout << tree.get(a, b) << endl;

    } else if(op == "modify_subtree") {
      int node;
      ll change;
      cin >> node >> change;
      node--;

      auto [a, b] = hld.subtree(node);
      tree.modify(a, b, change);
    }
  }
}
