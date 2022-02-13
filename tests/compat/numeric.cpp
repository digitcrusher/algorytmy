#include "compat/numeric.hpp"
#include <iostream>
#include <tuple>
#include <vector>

int main() {
  vector<tuple<int, int, int>> const gcd_tests = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1},
    {0, 123, 123},
    {2, 2, 2},
    {4, 6, 2},
    {4, 12, 4},
  };
  for(auto [a, b, c]: gcd_tests) {
    cout << "auto gcd " << a << " " << b << " " << c << endl;
    assert(gcd(a, b) == c);
    assert(gcd(-a, b) == c);
    assert(gcd(a, -b) == c);
    assert(gcd(-a, -b) == c);
  }

  vector<tuple<int, int, int>> const lcm_tests = {
    {1, 1, 1},
    {2, 2, 2},
    {3, 3, 3},
    {4, 4, 4},
    {1, 2, 2},
    {2, 3, 6},
    {3, 4, 12},
    {4, 5, 20},
  };
  for(auto [a, b, c]: lcm_tests) {
    cout << "auto lcm " << a << " " << b << " " << c << endl;
    assert(lcm(a, b) == c);
    assert(lcm(-a, b) == c);
    assert(lcm(a, -b) == c);
    assert(lcm(-a, -b) == c);
  }

  while(true) {
    string op;
    ll a, b;
    cin >> op >> a >> b;
    if(!cin) break;
    if(op == "gcd") {
      cout << gcd(a, b) << endl;
    } else if(op == "lcm") {
      cout << lcm(a, b) << endl;
    }
  }
}
