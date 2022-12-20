#include "ds/segment_tree/range_range_no_propagation.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;
  vector<int> init(n);
  for(auto &num: init) {
    cin >> num;
  }

  auto apply_change = [](int val, int change, int elemc) {
    return val + change * elemc;
  };
  SegmentTreeNoPropagation<
    int, plus<int>,
    int, decltype(apply_change), plus<int>
  > tree(init, plus<int>(), apply_change);

  while(true) {
    string op;
    int a, b;
    cin >> op >> a >> b;
    if(!cin) break;
    a--, b--;

    if(op == "get") {
      cout << tree.get(a, b) << endl;
    } else if(op == "modify") {
      int c;
      cin >> c;
      if(!cin) break;
      tree.modify(a, b, c);
    }
  }
}
