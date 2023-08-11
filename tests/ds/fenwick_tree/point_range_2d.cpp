#include "ds/fenwick_tree/point_range_2d.hpp"
#include "iostream.hpp"

int main() {
  int w, h;
  cin >> w >> h;
  vector init(h, vector<ll>(w));
  cin >> init;

  FenwickTree2D<ll, plus<ll>, minus<ll>, ll, plus<ll>> tree(init);

  while(cin) {
    string op;
    cin >> op;

    if(op == "get") {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      x1--, y1--, x2--, y2--;

      cout << tree.get(x1, y1, x2, y2) << endl;

    } else if(op == "modify") {
      int x, y;
      ll change;
      cin >> x >> y >> change;
      x--, y--;

      tree.modify(x, y, change);
    }
  }
}
