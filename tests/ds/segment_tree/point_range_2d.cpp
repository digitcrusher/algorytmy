#include "ds/segment_tree/point_range_2d.hpp"
#include <iostream>

int main() {
  int w, h;
  cin >> w >> h;
  vector init(h, vector<int>(w));
  for(auto &row: init) {
    for(auto &num: row) {
      cin >> num;
    }
  }

  SegmentTreePointRange2D<int, plus<int>> tree(init);

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "get") {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      if(!cin) break;
      x1--, y1--, x2--, y2--;
      cout << tree.get(x1, y1, x2, y2) << endl;
    } else if(op == "set") {
      int x, y, val;
      cin >> x >> y >> val;
      if(!cin) break;
      x--, y--;
      tree.set(x, y, val);
    } else if(op == "modify") {
      int x, y, change;
      cin >> x >> y >> change;
      if(!cin) break;
      x--, y--;
      tree.set(x, y, tree.nodes[tree.y_base_offset + y][tree.x_base_offset + x] + change);
    }
  }
}
