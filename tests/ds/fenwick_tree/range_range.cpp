#include "ds/fenwick_tree/range_range.hpp"
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
  FenwickTreeRangeRange<
    int, plus<int>, minus<int>,
    int, decltype(apply_change), plus<int>, negate<int>
  > tree(init, 0, plus<int>(), minus<int>(), apply_change);

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
