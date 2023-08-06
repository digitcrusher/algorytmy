#include "ds/implicit_treap.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;
  vector<ll> init(n);
  for(auto &i: init) {
    cin >> i;
  }

  auto treap = ImplicitTreap<ll, plus<ll>>::from(init);

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "rotate") {
      int idx;
      cin >> idx;
      if(!cin) break;
      idx--;

      rotate(treap, idx);

    } else if(op == "reverse") {
      int a, b;
      cin >> a >> b;
      if(!cin) break;
      a--, b--;

      reverse(treap, a, b);

    } else if(op == "get") {
      int a, b;
      cin >> a >> b;
      if(!cin) break;
      a--, b--;

      cout << treap->get(a, b) << endl;

    } else if(op == "print") {
      cout << treap << endl;
    }
  }
}
