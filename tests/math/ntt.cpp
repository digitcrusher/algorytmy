#include "math/ntt.hpp"
#include <iostream>

int main() {
  while(true) {
    string op;
    ll mod;
    int n;
    cin >> op >> mod >> n;
    vector<ll> a(n);
    for(ll &num: a) {
      cin >> num;
    }
    if(!cin) break;

    if(op == "dft") {
      ntt(a, mod);
    } else if(op == "idft") {
      ntt(a, mod, true);
    } else if(op == "mul") {
      int m;
      cin >> m;
      vector<ll> b(m);
      for(ll &num: b) {
        cin >> num;
      }
      if(!cin) break;
      mul(a, b, mod);
    }

    for(ll num: a) {
      cout << num << " ";
    }
    cout << endl;
  }
}
