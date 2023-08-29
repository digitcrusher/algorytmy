#include "ds/fenwick_tree/point_range.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<ll> init(n);
  cin >> init;

  FenwickTree<ll, plus<>, minus<>, ll, plus<>> tree(init);

  while(cin) {
    string op;
    cin >> op;

    if(op == "get") {
      int a, b;
      cin >> a >> b;
      a--, b--;

      cout << tree.get(a, b) << endl;

    } else if(op == "modify") {
      int idx;
      ll change;
      cin >> idx >> change;
      idx--;

      tree.modify(idx, change);
    }
  }
}
