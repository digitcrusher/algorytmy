#include "math/crt.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    vector<ll> rems(n), mods(n);
    for(int i = 0; i < n; i++) {
      cin >> rems[i] >> mods[i];
    }

    auto result = crt(rems, mods);
    if(result) {
      cout << result->soln << " " << result->mod << endl;
      for(int i = 0; i < n; i++) {
        assert(result->soln % mods[i] == norm_mod(rems[i], mods[i]));
      }
    } else {
      cout << "nullopt" << endl;
    }
  }
}
