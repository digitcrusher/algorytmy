#include "math/ntt.hpp"
#include "iostream.hpp"

int main() {
  using Z = Z<MOD>;
  NTT<Z> ntt;

  while(cin) {
    string op;
    int n;
    cin >> op >> n;
    vector<Z> a(n);
    cin >> a;

    if(op == "dft") {
      ntt(a);

    } else if(op == "idft") {
      ntt(a, true);

    } else if(op == "conv") {
      int m;
      cin >> m;
      vector<Z> b(m);
      cin >> b;

      ntt.conv(a, b);
    }

    cout << a << endl;
  }
}
