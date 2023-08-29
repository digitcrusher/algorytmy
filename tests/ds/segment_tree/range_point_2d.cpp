#include "ds/segment_tree/range_point_2d.hpp"
#include "iostream.hpp"

int main() {
  int w, h;
  cin >> w >> h;
  vector init(h, vector<ll>(w));
  cin >> init;

  SegmentTreeRangePoint2D<ll, ll, plus<>, plus<>> tree(init, 0);

  while(cin) {
    string op;
    cin >> op;

    if(op == "get") {
      int x, y;
      cin >> x >> y;
      x--, y--;

      cout << tree.get(x, y) << endl;

    } else if(op == "modify") {
      int x1, y1, x2, y2;
      ll change;
      cin >> x1 >> y1 >> x2 >> y2 >> change;
      x1--, y1--, x2--, y2--;

      tree.modify(x1, y1, x2, y2, change);
    }
  }
}
