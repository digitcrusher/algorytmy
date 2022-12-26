#include "ds/dsu.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;

  DSU dsu(n);
  ExplicitDSU explicit_dsu(n);

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "setc") {
      cout << dsu.setc << endl;
      assert(dsu.setc == explicit_dsu.setc);
    } else {
      int a;
      cin >> a;
      if(!cin) break;
      a--;

      if(op == "size") {
        int result = dsu.size[dsu.find(a)];
        cout << result << endl;
        assert(result = explicit_dsu.sets[explicit_dsu.find(a)].size());
      } else if(op == "find") {
        int result = dsu.find(a);
        cout << result + 1 << endl;
        assert(result == explicit_dsu.find(a));
      } else if(op == "merge") {
        int b;
        cin >> b;
        if(!cin) break;
        b--;
        bool result = dsu.merge(a, b);
        cout << boolalpha << result << endl;
        assert(result == explicit_dsu.merge(a, b));
      } else if(op == "set") {
        for(int i: explicit_dsu.sets[explicit_dsu.find(a)]) {
          cout << i + 1 << " ";
        }
        cout << endl;
      }
    }
  }
}
