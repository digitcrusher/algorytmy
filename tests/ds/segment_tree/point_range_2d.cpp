#include "ds/segment_tree/point_range_2d.hpp"
#include "iostream.hpp"

int main() {
  int w, h;
  cin >> w >> h;
  vector init(h, vector<ll>(w));
  cin >> init;

  SegmentTreePointRange2D<ll, plus<>> tree(init, 0);

  while(cin) {
    string op;
    cin >> op;

    if(op == "get") {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      x1--, y1--, x2--, y2--;

      cout << tree.get(x1, y1, x2, y2) << endl;

    } else if(op == "set") {
      int x, y;
      ll val;
      cin >> x >> y >> val;
      x--, y--;

      tree.set(x, y, val);

    } else if(op == "modify") {
      int x, y;
      ll change;
      cin >> x >> y >> change;
      x--, y--;

      tree.set(x, y, tree.nodes[tree.y_base_offset + y][tree.x_base_offset + x] + change);
    }
  }
}
