#include "math/eulers_phi.hpp"
#include "math/factor.hpp"
#include <iostream>

int main() {
  while(true) {
    ll n;
    cin >> n;
    if(!cin) break;
    cout << eulers_phi(n, factor_pollard_rho(n)) << endl;
  }
}
