#include "math/factor.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    ll x;
    cin >> x;

    auto result = factor_pollard_rho(x);
    for(auto [prime, exp]: result) {
      for(int i = 0; i < exp; i++) {
        cout << prime << " ";
      }
    }
    cout << endl;
  }
}
