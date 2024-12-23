#include "math/div.hpp"
#include "math/factor.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    ll x;
    cin >> x;

    auto factors = factor_pollard_rho(x);
    cout << divc(factors) << endl;
    cout << div_sum(factors) << endl;
    cout << div_product<Z<MOD>>(factors) << endl;
  }
}
