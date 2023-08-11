#include "ds/segment_tree/point_range.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<ll> init(n);
  cin >> init;

  SegmentTreePointRange<ll, plus<ll>> tree(init, 0);

  while(cin) {
    string op;
    cin >> op;

    if(op == "get") {
      int a, b;
      cin >> a >> b;
      a--, b--;

      cout << tree.get(a, b) << endl;

    } else if(op == "set") {
      int idx;
      ll val;
      cin >> idx >> val;
      idx--;

      tree.set(idx, val);
    }
  }
}
