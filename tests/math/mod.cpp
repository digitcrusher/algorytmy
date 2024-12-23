#include "math/mod.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    string op;
    cin >> op;

    if(op == "norm_mod") {
      ll x, mod;
      cin >> x >> mod;

      cout << norm_mod(x, mod) << endl;

    } else if(op == "mod_pow") {
      ll a, b, mod;
      cin >> a >> b >> mod;

      cout << mod_pow(a, b, mod) << endl;
    }
  }
}
