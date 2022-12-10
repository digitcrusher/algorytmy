#include "math/factor.hpp"
#include <iostream>

int main() {
  while(true) {
    ll x;
    cin >> x;
    if(!cin) break;
    auto result = factor_pollard_rho(x);
    for(auto [p, k]: result) {
      for(int i = 0; i < k; i++) {
        cout << p << " ";
      }
    }
    cout << endl;
  }
}
