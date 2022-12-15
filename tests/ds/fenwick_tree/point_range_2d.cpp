#include "ds/fenwick_tree/point_range_2d.hpp"
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

  FenwickTree2D<int, plus<int>, minus<int>, int, plus<int>> tree(init);

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
    } else if(op == "modify") {
      int x, y, change;
      cin >> x >> y >> change;
      if(!cin) break;
      x--, y--;
      tree.modify(x, y, change);
    }
  }
}
