#include "math/mod.hpp"
#include <iostream>

int main() {
  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "norm_mod") {
      ll x, mod;
      cin >> x >> mod;
      if(!cin) break;
      cout << norm_mod(x, mod) << endl;

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
      ll x, mod;
      cin >> x >> mod;
      if(!cin) break;
      auto result = mod_inv(x, mod);
      if(result == nullopt) {
        cout << "nullopt" << endl;
      } else {
        cout << *result << endl;
        assert(norm_mod(x * *result, mod) == 1);
      }

    } else if(op == "mod_inv_prime") {
      ll x, mod;
      cin >> x >> mod;
      if(!cin) break;
      auto result = mod_inv_prime(x, mod);
      if(result == nullopt) {
        cout << "nullopt" << endl;
      } else {
        cout << *result << endl;
        assert(norm_mod(x * *result, mod) == 1);
      }
    }
  }
}
