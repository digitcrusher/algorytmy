#include "math/diophantine.hpp"
#include <iostream>

int main() {
  ll a, b, c;
  optional<LinDiophantineSoln> result = nullopt;

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "solve") {
      cin >> a >> b >> c;
      if(!cin) break;
      result = solve_lin_diophantine(a, b, c);

    } else if(op == "shift") {
      int step;
      cin >> step;
      if(!cin) break;
      if(result != nullopt) {
        result = result->shift_soln(step);
      }
    }

    if(result == nullopt) {
      cout << "nullopt" << endl;
    } else {
      cout << result->x << " " << result->y << " " << result->gcd_ab << endl;
      assert(a * result->x + b * result->y == c);
    }
  }
}
