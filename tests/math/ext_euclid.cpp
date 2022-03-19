#include "math/ext_euclid.hpp"
#include <iostream>
#include <optional>

int main() {
  optional<ExtEuclidResult> result = nullopt;
  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "solve") {
      ll a, b;
      cin >> a >> b;
      if(!cin) break;
      result = ext_euclid(a, b);

    } else if(op == "shift") {
      int step;
      cin >> step;
      if(!cin) break;
      if(result != nullopt) {
        result = result->shift_coefs(step);
      }
    }

    if(result != nullopt) {
      cout << result->gcd << " " << result->x << " " << result->y << endl;
      assert(result->a * result->x + result->b * result->y == result->gcd);
    }
  }
}
