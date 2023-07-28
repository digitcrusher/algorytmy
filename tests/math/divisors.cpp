#include "math/divisors.hpp"
#include "math/factor.hpp"
#include <iostream>

int main() {
  while(true) {
    string op;
    ll x;
    cin >> op >> x;
    if(!cin) break;

    auto factors = factor_pollard_rho(x);
    if(op == "divc") {
      cout << divc(factors) << endl;
    } else if(op == "div_sum") {
      cout << div_sum(factors) << endl;
    } else if(op == "div_product") {
      cout << div_product(factors) << endl;
    }
  }
}
