#include "ds/segment_tree/point_range.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;
  vector<int> init(n);
  for(auto &num: init) {
    cin >> num;
  }

  SegmentTreePointRange<int, plus<int>> tree(init);

  while(true) {
    string op;
    int a, b;
    cin >> op >> a >> b;
    if(!cin) break;
    a--;

    if(op == "get") {
      b--;
      cout << tree.get(a, b) << endl;
    } else if(op == "set") {
      tree.set(a, b);
    }
  }
}
