#include "math/factor.hpp"
#include <iostream>

int main() {
  while(true) {
    ll n;
    cin >> n;
    if(!cin) break;
    auto result = factor_pollard_rho(n);
    for(auto [p, k]: result) {
      for(int i = 0; i < k; i++) {
        cout << p << " ";
      }
    }
    cout << endl;
  }
}
