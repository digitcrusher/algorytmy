#include "ds/dsu/undoable.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;

  UndoableDSU dsu(n);

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "setc") {
      cout << dsu.setc << endl;

    } else if(op == "size") {
      int node;
      cin >> node;
      if(!cin) break;
      node--;

      cout << dsu.size[dsu.find(node)] << endl;

    } else if(op == "find") {
      int node;
      cin >> node;
      if(!cin) break;
      node--;

      cout << dsu.find(node) + 1 << endl;

    } else if(op == "merge") {
      int a, b;
      cin >> a >> b;
      if(!cin) break;
      a--, b--;

      cout << boolalpha << dsu.merge(a, b) << endl;

    } else if(op == "undo") {
      cout << boolalpha << dsu.undo() << endl;
    }
  }
}
