#include "ds/dsu.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;

  DSU dsu(n);

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "setc") {
      cout << dsu.setc << endl;
    } else {
      int a;
      cin >> a;
      if(!cin) break;
      a--;

      if(op == "size") {
        cout << dsu.size[dsu.find(a)] << endl;
      } else if(op == "find") {
        cout << dsu.find(a) + 1 << endl;
      } else if(op == "merge") {
        int b;
        cin >> b;
        if(!cin) break;
        b--;
        dsu.merge(a, b);
      }
    }
  }
}
