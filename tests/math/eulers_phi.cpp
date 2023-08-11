#include "math/eulers_phi.hpp"
#include "math/factor.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    ll x;
    cin >> x;

    cout << eulers_phi(x, factor_pollard_rho(x)) << endl;
  }
}
