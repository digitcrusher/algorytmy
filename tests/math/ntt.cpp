#include "math/ntt.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string op;
    ll mod;
    int n;
    cin >> op >> mod >> n;
    vector<ll> a(n);
    cin >> a;

    if(op == "dft") {
      ntt(a, mod);

    } else if(op == "idft") {
      ntt(a, mod, true);

    } else if(op == "mul") {
      int m;
      cin >> m;
      vector<ll> b(m);
      cin >> b;

      mul(a, b, mod);
    }

    cout << a << endl;
  }
}
