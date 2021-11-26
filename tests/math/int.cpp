#include "math/int.hpp"
#include <cmath>
#include <iostream>

int main() {
  assert(floor_log2(1) == 0);
  assert(floor_log2(2) == 1);
  assert(floor_log2(3) == 1);
  assert(floor_log2(4) == 2);
  assert(floor_log2(5) == 2);
  assert(floor_log2(6) == 2);
  assert(floor_log2(7) == 2);
  assert(floor_log2(8) == 3);
  assert(floor_log2(9) == 3);
  assert(floor_log2((1ull << 63) - 1) == 62);
  assert(floor_log2(1ull << 63) == 63);
  assert(floor_log2(~0ull) == 63);

  assert(ceil_log2(1) == 0);
  assert(ceil_log2(2) == 1);
  assert(ceil_log2(3) == 2);
  assert(ceil_log2(4) == 2);
  assert(ceil_log2(5) == 3);
  assert(ceil_log2(6) == 3);
  assert(ceil_log2(7) == 3);
  assert(ceil_log2(8) == 3);
  assert(ceil_log2(9) == 4);
  assert(ceil_log2((1ull << 63) - 1) == 63);
  assert(ceil_log2(1ull << 63) == 63);
  assert(ceil_log2(~0ull) == 64);

  assert(floor_div(-2, 2) == -1);
  assert(floor_div(-1, 2) == -1);
  assert(floor_div(0, 2) == 0);
  assert(floor_div(1, 2) == 0);
  assert(floor_div(2, 2) == 1);
  assert(floor_div(-2, -2) == 1);
  assert(floor_div(-1, -2) == 0);
  assert(floor_div(0, -2) == 0);
  assert(floor_div(1, -2) == -1);
  assert(floor_div(2, -2) == -1);

  assert(ceil_div(-2, 2) == -1);
  assert(ceil_div(-1, 2) == 0);
  assert(ceil_div(0, 2) == 0);
  assert(ceil_div(1, 2) == 1);
  assert(ceil_div(2, 2) == 1);
  assert(ceil_div(-2, -2) == 1);
  assert(ceil_div(-1, -2) == 1);
  assert(ceil_div(0, -2) == 0);
  assert(ceil_div(1, -2) == 0);
  assert(ceil_div(2, -2) == -1);

  srand(time(nullptr));

  for(int i = 0; i < 100; i++) {
    ll a = rand() % 201 - 100;
    ll b = rand() % 201 - 100;

    cout << "a = " << a << ", b = " << b << endl;

    if(a > 0) {
      assert(floor_log2(a) == floor(log2(a)));
      assert(ceil_log2(a) == ceil(log2(a)));
    }

    if(b != 0) {
      assert(floor((float) a / b) == floor_div(a, b));
      assert(ceil((float) a / b) == ceil_div(a, b));
    }
  }
}
