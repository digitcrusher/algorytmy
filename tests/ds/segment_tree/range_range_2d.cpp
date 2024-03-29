#include "ds/segment_tree/range_range_2d.hpp"
#include "iostream.hpp"

int main() {
  int w, h;
  cin >> w >> h;
  vector init(h, vector<ll>(w));
  cin >> init;

  struct ApplyChange {
    ll operator()(ll val, ll change, int elemc) {
      return val + change * elemc;
    }
  };
  SegmentTree2D<ll, plus<>, ll, ApplyChange, plus<>, multiplies<>> tree(init);

  while(cin) {
    string op;
    cin >> op;

    if(op == "get") {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      x1--, y1--, x2--, y2--;

      cout << tree.get(x1, y1, x2, y2) << endl;

    } else if(op == "modify") {
      int x1, y1, x2, y2;
      ll change;
      cin >> x1 >> y1 >> x2 >> y2 >> change;
      x1--, y1--, x2--, y2--;

      tree.modify(x1, y1, x2, y2, change);
    }
  }
}
