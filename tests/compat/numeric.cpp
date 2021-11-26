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

  cout << "gcd:" << endl;

  for(auto [a, b, c]: gcd_tests) {
    cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
    assert(gcd(a, b) == c);
    assert(gcd(-a, b) == c);
    assert(gcd(a, -b) == c);
    assert(gcd(-a, -b) == c);
  }

  cout << endl << "lcm:" << endl;

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
    cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
    assert(lcm(a, b) == c);
    assert(lcm(-a, b) == c);
    assert(lcm(a, -b) == c);
    assert(lcm(-a, -b) == c);
  }
}
