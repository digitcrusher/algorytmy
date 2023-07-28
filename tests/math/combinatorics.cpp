#include "math/combinatorics.hpp"
#include <iostream>

int main() {
  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "choose") {
      int n, k;
      ll mod;
      cin >> n >> k >> mod;
      if(!cin) break;

      cout << choose(n, k, mod) << endl;
      assert(choose_fac(n, k, mod) == choose_mul(n, k, mod));

    } else if(op == "any_in_uniq") {
      int n, k;
      ll mod;
      cin >> n >> k >> mod;
      if(!cin) break;

      cout << any_in_uniq(n, k, mod) << endl;

    } else if(op == "uniq_in_uniq") {
      int n, k;
      ll mod;
      cin >> n >> k >> mod;
      if(!cin) break;

      cout << uniq_in_uniq(n, k, mod) << endl;

    } else if(op == "subfac") {
      int n;
      ll mod;
      cin >> n >> mod;
      if(!cin) break;

      cout << subfac(n, mod) << endl;

    } else if(op == "burnside") {
      int n, k;
      ll mod;
      cin >> n >> k >> mod;
      if(!cin) break;

      cout << burnside(n, k, mod) << endl;

    } else if(op == "catalan") {
      int n;
      ll mod;
      cin >> n >> mod;
      if(!cin) break;

      cout << catalan(n, mod) << endl;
    }
  }
}
