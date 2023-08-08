#include "ds/dsu/explicit.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;

  ExplicitDSU dsu(n);

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

      cout << dsu.sets[dsu.find(node)].size() << endl;

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

    } else if(op == "set") {
      int node;
      cin >> node;
      if(!cin) break;
      node--;

      for(auto i: dsu.sets[dsu.find(node)]) {
        cout << i + 1 << " ";
      }
      cout << endl;
    }
  }
}
