#include "math/combinatorics.hpp"
#include <iostream>

int main() {
  while(true) {
    string op;
    ll n, k, mod;
    cin >> op >> n >> k >> mod;
    if(!cin) break;
    if(op == "choose") {
      cout << choose(n, k, mod) << endl;
      assert(choose_fac(n, k, mod) == choose_mul(n, k, mod));
    } else if(op == "any_in_uniq") {
      cout << any_in_uniq(n, k, mod) << endl;
    } else if(op == "uniq_in_uniq") {
      cout << uniq_in_uniq(n, k, mod) << endl;
    }
  }
}
