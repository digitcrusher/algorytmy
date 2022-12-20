#include "ds/segment_tree/range_range_2d.hpp"
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

  auto apply_change = [](int val, int change, int elemc) {
    return val + change * elemc;
  };
  SegmentTree2D<
    int, plus<int>,
    int, decltype(apply_change), plus<int>, multiplies<int>
  > tree(init, plus<int>(), apply_change);

  while(true) {
    string op;
    int x1, y1, x2, y2;
    cin >> op >> x1 >> y1 >> x2 >> y2;
    if(!cin) break;
    x1--, y1--, x2--, y2--;

    if(op == "get") {
      cout << tree.get(x1, y1, x2, y2) << endl;
    } else if(op == "modify") {
      int change;
      cin >> change;
      if(!cin) break;
      tree.modify(x1, y1, x2, y2, change);
    }
  }
}
