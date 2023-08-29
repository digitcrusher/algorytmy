#include "ds/fenwick_tree/range_point.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<ll> init(n);
  cin >> init;

  FenwickTreeRangePoint<ll, ll, plus<>, plus<>, negate<>> tree(init, 0);

  while(cin) {
    string op;
    cin >> op;

    if(op == "get") {
      int idx;
      cin >> idx;
      idx--;

      cout << tree.get(idx) << endl;

    } else if(op == "modify") {
      int a, b;
      ll change;
      cin >> a >> b >> change;
      a--, b--;

      tree.modify(a, b, change);
    }
  }
}
