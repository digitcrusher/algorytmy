#include "ds/fenwick_tree/range_point_2d.hpp"
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

  FenwickTreeRangePoint2D<int, int, plus<int>, plus<int>, negate<int>> tree(init, 0);

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "get") {
      int x, y;
      cin >> x >> y;
      if(!cin) break;
      x--, y--;
      cout << tree.get(x, y) << endl;
    } else if(op == "modify") {
      int x1, y1, x2, y2, change;
      cin >> x1 >> y1 >> x2 >> y2 >> change;
      if(!cin) break;
      x1--, y1--, x2--, y2--;
      tree.modify(x1, y1, x2, y2, change);
    }
  }
}
