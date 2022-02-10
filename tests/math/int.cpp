#include "math/int.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
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

    cout << "auto " << a << " " << b << endl;

    if(a > 0) {
      assert(floor_log2(a) == floor(log2(a)));
      assert(ceil_log2(a) == ceil(log2(a)));
    }

    if(b != 0) {
      assert(floor_div(a, b) == floor((ld) a / b));
      assert(ceil_div(a, b) == ceil((ld) a / b));
    }
  }

  while(true) {
    string op;
    cin >> op;
    if(!cin) break;

    if(op == "floor_log2") {
      ull a;
      cin >> a;
      if(!cin) break;
      ull result = floor_log2(a);
      cout << result << endl;
      assert(result == floor(log2(a)));

    } else if(op == "ceil_log2") {
      ull a;
      cin >> a;
      if(!cin) break;
      ull result = ceil_log2(a);
      cout << result << endl;
      assert(result == ceil(log2(a)));

    } else if(op == "floor_div") {
      ll a, b;
      cin >> a >> b;
      if(!cin) break;
      ll result = floor_div(a, b);
      cout << result << endl;
      assert(result == floor((ld) a / b));

    } else if(op == "ceil_div") {
      ll a, b;
      cin >> a >> b;
      if(!cin) break;
      ll result = ceil_div(a, b);
      cout << result << endl;
      assert(result == ceil((ld) a / b));
    }
  }
}
