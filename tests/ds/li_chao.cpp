#include "ds/li_chao.hpp"
#include <iostream>

int main() {
  int min_x, max_x;
  LinFunc first;
  cin >> min_x >> max_x >> first.a >> first.b;

  LiChao tree(min_x, max_x, first);

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "get") {
      int x;
      cin >> x;
      if(!cin) break;

      cout << tree.get(x) << endl;

    } else if(op == "insert") {
      LinFunc func;
      cin >> func.a >> func.b;
      if(!cin) break;

      tree.insert(func);
    }
  }
}
