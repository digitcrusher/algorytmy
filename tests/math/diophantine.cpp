#include "math/diophantine.hpp"
#include "iostream.hpp"

int main() {
  ll a, b, c;
  optional<LinDiophantineSoln> result;

  while(cin) {
    string op;
    cin >> op;

    if(op == "solve") {
      cin >> a >> b >> c;

      result = solve_lin_diophantine(a, b, c);

    } else if(op == "shift") {
      int step;
      cin >> step;

      if(result) {
        result = result->shift(step);
      }
    }

    if(result) {
      cout << result->x << " " << result->y << " " << result->gcd_ab << endl;
      assert(a * result->x + b * result->y == c);
    } else {
      cout << "nullopt" << endl;
    }
  }
}
