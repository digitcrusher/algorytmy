#include "math/discrete_log.hpp"
#include <iostream>

int main() {
  while(true) {
    ll a, b, mod, k;
    cin >> a >> b >> mod >> k;
    if(!cin) break;

    auto result = discrete_log(a, b, mod, k);
    if(result == nullopt) {
      cout << "nullopt" << endl;
    } else {
      cout << *result << endl;
      assert(norm_mod(k * mod_pow(a, *result, mod), mod) == norm_mod(b, mod));
    }
  }
}
