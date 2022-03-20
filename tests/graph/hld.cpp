#include "graph/hld.hpp"
#include "ds/segment_tree.hpp"
#include <iostream>
#include <optional>

int main() {
  optional<HLD> hld;
  auto apply_change = [](int val, int change, int elemc) {
    return val + change * elemc;
  };
  optional<SegmentTree<int, plus<int>, int, decltype(apply_change), plus<int>>> tree;

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "graph") {
      int n, root;
      cin >> n >> root;
      if(!cin) break;
      root--;

      vector<vector<int>> adj(n);
      for(int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        if(!cin) break;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
      }
      if(!cin) break;
      hld = HLD(adj, root);

      vector<int> elems(n);
      for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        if(!cin) break;
        elems[hld->entry[i]] = num;
      }
      if(!cin) break;
      tree.emplace(elems, plus<int>(), apply_change);

    } else if(op == "get_path") {
      int a, b;
      cin >> a >> b;
      if(!cin) break;
      a--, b--;

      int result = 0;
      auto segs = hld->path(a, b);
      for(auto [l, r]: segs) {
        result = tree->sum(result, tree->get(l, r));
      }
      cout << result << endl;

    } else if(op == "modify_path") {
      int a, b, change;
      cin >> a >> b >> change;
      if(!cin) break;
      a--, b--;

      auto segs = hld->path(a, b);
      for(auto [l, r]: segs) {
        tree->modify(l, r, change);
      }

    } else if(op == "get_subtree") {
      int node;
      cin >> node;
      if(!cin) break;
      node--;

      auto seg = hld->subtree(node);
      cout << tree->get(seg.first, seg.second) << endl;

    } else if(op == "modify_subtree") {
      int node, change;
      cin >> node >> change;
      if(!cin) break;
      node--;

      auto seg = hld->subtree(node);
      tree->modify(seg.first, seg.second, change);
    }
  }
}
