#include "ds/fenwick_tree.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;
  vector<int> init(n);
  for(auto &num: init) {
    cin >> num;
  }

  FenwickTree<int, plus<int>, minus<int>, int, plus<int>> tree(init);

  while(true) {
    string op;
    int a, b;
    cin >> op >> a >> b;
    if(!cin) break;
    if(op == "get") {
      a--, b--;
      cout << tree.get(a, b) << endl;
    } else if(op == "modify") {
      a--;
      tree.modify(a, b);
    }
  }
}
