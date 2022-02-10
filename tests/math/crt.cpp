#include "math/crt.hpp"
#include <iostream>

int main() {
  while(true) {
    int n;
    cin >> n;
    if(!cin) break;
    vector<ll> rems(n), mods(n);
    for(int i = 0; i < n; i++) {
      cin >> rems[i] >> mods[i];
      if(!cin) break;
    }

    auto result = crt(rems, mods);
    if(result == nullopt) {
      cout << "nullopt" << endl;
    } else {
      cout << result->soln << " " << result->mod << endl;
      for(int i = 0; i < n; i++) {
        assert(result->soln % mods[i] == norm_mod(rems[i], mods[i]));
      }
    }
  }
}
