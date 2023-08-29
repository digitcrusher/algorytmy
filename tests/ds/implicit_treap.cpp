#include "ds/implicit_treap.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<ll> init(n);
  cin >> init;

  auto treap = ImplicitTreap<ll, plus<>>::from(init);

  while(cin) {
    string op;
    cin >> op;

    if(op == "rotate") {
      int idx;
      cin >> idx;
      idx--;

      rotate(treap, idx);

    } else if(op == "reverse") {
      int a, b;
      cin >> a >> b;
      a--, b--;

      reverse(treap, a, b);

    } else if(op == "get") {
      int a, b;
      cin >> a >> b;
      a--, b--;

      cout << treap->get(a, b) << endl;

    } else if(op == "print") {
      cout << treap << endl;
    }
  }
}
