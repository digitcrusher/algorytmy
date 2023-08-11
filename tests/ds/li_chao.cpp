#include "ds/li_chao.hpp"
#include "iostream.hpp"

int main() {
  int min_x, max_x;
  LinFunc first;
  cin >> min_x >> max_x >> first.a >> first.b;

  LiChao tree(min_x, max_x, first);

  while(cin) {
    string op;
    cin >> op;

    if(op == "get") {
      int x;
      cin >> x;

      cout << tree.get(x) << endl;

    } else if(op == "insert") {
      LinFunc func;
      cin >> func.a >> func.b;

      tree.insert(func);
    }
  }
}
