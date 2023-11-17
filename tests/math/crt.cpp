#include "math/crt.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    vector<ll> rems(n), mods(n);
    for(auto i: v::iota(0, n)) {
      cin >> rems[i] >> mods[i];
    }

    auto result = crt(rems, mods);
    if(result) {
      cout << result->soln << " " << result->mod << endl;
      for(auto i: v::iota(0, n)) {
        assert(result->soln % mods[i] == norm_mod(rems[i], mods[i]));
      }
    } else {
      cout << "nullopt" << endl;
    }
  }
}
