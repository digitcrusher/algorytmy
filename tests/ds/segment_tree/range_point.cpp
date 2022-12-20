#include "ds/segment_tree/range_point.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;
  vector<int> init(n);
  for(auto &num: init) {
    cin >> num;
  }

  SegmentTreeRangePoint<int, int, plus<int>, plus<int>> tree(init, 0);

  while(true) {
    string op;
    int a;
    cin >> op >> a;
    if(!cin) break;
    a--;

    if(op == "get") {
      cout << tree.get(a) << endl;
    } else if(op == "modify") {
      int b, c;
      cin >> b >> c;
      if(!cin) break;
      b--;
      tree.modify(a, b, c);
    }
  }
}
