#include "math/eulers_phi.hpp"
#include "math/factor.hpp"
#include <iostream>

int main() {
  while(true) {
    ll x;
    cin >> x;
    if(!cin) break;
    cout << eulers_phi(x, factor_pollard_rho(x)) << endl;
  }
}
