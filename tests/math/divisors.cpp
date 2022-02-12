#include "math/divisors.hpp"
#include "math/factor.hpp"
#include <iostream>

int main() {
  while(true) {
    string op;
    ll n;
    cin >> op >> n;
    if(!cin) break;
    auto factors = factor_pollard_rho(n);
    if(op == "divc") {
      cout << divc(factors) << endl;
    } else if(op == "div_sum") {
      cout << div_sum(factors) << endl;
    }
  }
}
