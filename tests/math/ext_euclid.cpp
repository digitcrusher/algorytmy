#include "math/ext_euclid.hpp"
#include "iostream.hpp"

int main() {
  ExtEuclid result;

  while(cin) {
    string op;
    cin >> op;

    if(op == "solve") {
      ll a, b;
      cin >> a >> b;

      result = ext_euclid(a, b);

    } else if(op == "shift") {
      int step;
      cin >> step;

      result = result.shift(step);
    }

    cout << result.gcd << " " << result.x << " " << result.y << endl;
    assert(result.a * result.x + result.b * result.y == result.gcd);
  }
}
