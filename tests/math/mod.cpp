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

    } else if(op == "mod_mul") {
      ll a, b, mod;
      cin >> a >> b >> mod;

      cout << mod_mul(a, b, mod) << endl;

    } else if(op == "mod_pow") {
      ll a, b, mod;
      cin >> a >> b >> mod;

      cout << mod_pow(a, b, mod) << endl;

    } else if(op == "mod_inv") {
      ll x, mod;
      cin >> x >> mod;

      auto result = mod_inv(x, mod);
      if(result) {
        cout << *result << endl;
        assert(mod_mul(x, *result, mod) == 1);
      } else {
        cout << "nullopt" << endl;
      }

    } else if(op == "mod_inv_prime") {
      ll x, mod;
      cin >> x >> mod;

      auto result = mod_inv_prime(x, mod);
      if(result) {
        cout << *result << endl;
        assert(mod_mul(x, *result, mod) == 1);
      } else {
        cout << "nullopt" << endl;
      }
    }
  }
}
