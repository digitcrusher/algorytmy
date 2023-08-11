#include "math/div.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    ll x, mod;
    cin >> x >> mod;

    auto factors = factor_pollard_rho(x);
    cout << divc(factors) << endl;
    cout << div_sum(factors) << endl;
    cout << div_product(factors, mod) << endl;
  }
}
