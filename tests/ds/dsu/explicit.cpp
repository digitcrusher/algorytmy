#include "ds/dsu/explicit.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;

  ExplicitDSU dsu(n);

  while(cin) {
    string op;
    cin >> op;

    if(op == "setc") {
      cout << dsu.setc << endl;

    } else if(op == "size") {
      int node;
      cin >> node;
      node--;

      cout << dsu.sets[dsu.find(node)].size() << endl;

    } else if(op == "find") {
      int node;
      cin >> node;
      node--;

      cout << dsu.find(node) + 1 << endl;

    } else if(op == "merge") {
      int a, b;
      cin >> a >> b;
      a--, b--;

      cout << boolalpha << dsu.merge(a, b) << endl;

    } else if(op == "set") {
      int node;
      cin >> node;
      node--;

      for(auto i: dsu.sets[dsu.find(node)]) {
        cout << i + 1 << " ";
      }
      cout << endl;
    }
  }
}
