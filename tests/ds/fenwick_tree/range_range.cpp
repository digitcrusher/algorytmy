#include "ds/fenwick_tree/range_range.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<ll> init(n);
  cin >> init;

  struct ApplyChange {
    ll operator()(ll val, ll change, int elemc) {
      return val + change * elemc;
    }
  };
  FenwickTreeRangeRange<
    ll, plus<ll>, minus<ll>,
    ll, ApplyChange, plus<ll>, negate<ll>
  > tree(init, 0);

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
