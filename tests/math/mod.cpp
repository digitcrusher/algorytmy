#include "math/mod.hpp"
#include <iostream>

int main() {
  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "norm_mod") {
      ll a, mod;
      cin >> a >> mod;
      if(!cin) break;
      cout << norm_mod(a, mod) << endl;

    } else if(op == "mod_mul") {
      ll a, b, mod;
      cin >> a >> b >> mod;
      if(!cin) break;
      cout << mod_mul(a, b, mod) << endl;

    } else if(op == "mod_pow") {
      ll a, b, mod;
      cin >> a >> b >> mod;
      if(!cin) break;
      cout << mod_pow(a, b, mod) << endl;

    } else if(op == "mod_inv") {
      ll a, mod;
      cin >> a >> mod;
      if(!cin) break;
      auto result = mod_inv(a, mod);
      if(result == nullopt) {
        cout << "nullopt" << endl;
      } else {
        cout << *result << endl;
        assert(norm_mod(a * *result, mod) == 1);
      }

    } else if(op == "mod_inv_prime") {
      ll a, mod;
      cin >> a >> mod;
      if(!cin) break;
      ll result = mod_inv_prime(a, mod);
      cout << result << endl;
      assert(norm_mod(a * result, mod) == 1);
    }
  }
}
