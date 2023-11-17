#include "math/factor.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    ll x;
    cin >> x;

    auto result = factor_pollard_rho(x);
    for(auto [prime, exp]: result) {
      for(auto i: v::iota(0, exp)) {
        cout << prime << " ";
      }
    }
    cout << endl;
  }
}
