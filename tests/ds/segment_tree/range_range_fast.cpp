#include "ds/segment_tree/range_range_fast.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<ll> init(n);
  cin >> init;

  struct ApplyChange {
    ll operator()(ll val, ll change, int elemc) {
      return val + change * elemc;
    };
  };
  SegmentTree<ll, plus<ll>, ll, ApplyChange, plus<ll>> tree(init);

  while(cin) {
    string op;
    cin >> op;

    if(op == "get") {
      int a, b;
      cin >> a >> b;
      a--, b--;

      cout << tree.get(a, b) << endl;

    } else if(op == "modify") {
      int a, b;
      ll change;
      cin >> a >> b >> change;
      a--, b--;

      tree.modify(a, b, change);
    }
  }
}
