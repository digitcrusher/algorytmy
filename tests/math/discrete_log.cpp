#include "math/discrete_log.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    ll a, b, mod, k;
    cin >> a >> b >> mod >> k;

    auto result = discrete_log(a, b, mod, k);
    if(result) {
      cout << *result << endl;
      assert(mod_mul(k, mod_pow(a, *result, mod), mod) == norm_mod(b, mod));
    } else {
      cout << "nullopt" << endl;
    }
  }
}
