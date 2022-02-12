#include "math/factor.hpp"
#include <iostream>

int main() {
  while(true) {
    ll n;
    cin >> n;
    if(!cin) break;
    auto result = factor_pollard_rho(n);
    for(ll i: result) {
      cout << i << " ";
    }
    cout << endl;
  }
}
