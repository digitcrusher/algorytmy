#include "math/eulers_phi.hpp"
#include "math/factor.hpp"
#include <iostream>

int main() {
  while(true) {
    ll n;
    cin >> n;
    if(!cin) break;
    auto factors = factor_pollard_rho(n);
    cout << eulers_phi(n, factors) << endl;
  }
}
