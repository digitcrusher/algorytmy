#include "math/int.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  assert(countl_zero(0ull) == 64);
  assert(countl_zero(1ull) == 63);
  assert(countl_zero(2ull) == 62);
  assert(countl_zero(3ull) == 62);
  assert(countl_zero(4ull) == 61);
  assert(countl_zero(5ull) == 61);
  assert(countl_zero(6ull) == 61);
  assert(countl_zero(7ull) == 61);
  assert(countl_zero(8ull) == 60);
  assert(countl_zero(9ull) == 60);
  assert(countl_zero(~0u) == 0);
  assert(countl_zero(~0ull) == 0);
  assert(countl_zero(1u) == 31);
  assert(countl_zero(1u << 31) == 0);
  assert(countl_zero(1ull << 63) == 0);
  assert(countl_zero(~0ull >> 1) == 1);
  assert(countl_zero(~0ull << 1) == 0);

  cout << "__builtin_clzll(0) = " << __builtin_clzll(0) << endl;
  ull a = 1;
  cout << "__builtin_clzll(" << (a - 1) << ") = " << __builtin_clzll(a - 1) << endl;
  ull b = a - 1;
  cout << "__builtin_clzll(" << b << ") = " << __builtin_clzll(b) << endl;
  /*
   * Powyższy kod skompilowany z GCC 9.3.0 na AMD Ryzen 5 3600 wypisuje:
   *
   *   __builtin_clzll(0) = 64
   *   __builtin_clzll(0) = 63
   *   __builtin_clzll(0) = [losowa wartość]
   *
   * Odkryłem to podczas debugowania ceil_log2. Dzieje się tak, ponieważ
   * __builtin_clzll jest intrinsic'iem, co oznacza, że jest zamieniany przez
   * GCC na instrukcję procesora podczas kompilacji. Z domyślnymi ustawieniami
   * GCC dla x86 __builtin_clzll zamieniane jest na kombinację instrukcji bsr i
   * xor; więc w drugim przypadku wykonywany jest bsr/xor na rejestrze, a w
   * trzecim na komórce w pamięci RAM (zmiennej na stosie). W pierwszym
   * przypadku wartość jest jeszcze obliczana podczas kompilacji, więc jest
   * poprawna. Instrukcja bsr jest niezdefiniowana dla 0 (może zwrócić
   * cokolwiek), dlatego zwraca takie wyniki. Nawet sama dokumentacja GCC mówi,
   * że __builtin_clzll(0) jest niezdefiniowane. Natomiast z -march=haswell
   * __builtin_clzll zamieniane jest na lzcnt, które już zwraca poprawny wynik
   * dla każdego z dwóch przypadków. Tę wiedzę zawdzięczam "wreien" z serwera
   * Discord Together C & C++.
   */

  assert(countr_zero(0ull) == 64);
  assert(countr_zero(1ull) == 0);
  assert(countr_zero(2ull) == 1);
  assert(countr_zero(3ull) == 0);
  assert(countr_zero(4ull) == 2);
  assert(countr_zero(5ull) == 0);
  assert(countr_zero(6ull) == 1);
  assert(countr_zero(7ull) == 0);
  assert(countr_zero(8ull) == 3);
  assert(countr_zero(9ull) == 0);
  assert(countr_zero(~0u) == 0);
  assert(countr_zero(~0ull) == 0);
  assert(countr_zero(1u) == 0);
  assert(countr_zero(1u << 31) == 31);
  assert(countr_zero(1ull << 63) == 63);
  assert(countr_zero(~0ull >> 1) == 0);
  assert(countr_zero(~0ull << 1) == 1);

  assert(popcount(0ull) == 0);
  assert(popcount(1ull) == 1);
  assert(popcount(2ull) == 1);
  assert(popcount(3ull) == 2);
  assert(popcount(4ull) == 1);
  assert(popcount(5ull) == 2);
  assert(popcount(6ull) == 2);
  assert(popcount(7ull) == 3);
  assert(popcount(8ull) == 1);
  assert(popcount(9ull) == 2);
  assert(popcount(~0u) == 32);
  assert(popcount(~0ull) == 64);
  assert(popcount(1u) == 1);
  assert(popcount(1u << 31) == 1);
  assert(popcount(1ull << 63) == 1);
  assert(popcount(~0ull >> 1) == 63);
  assert(popcount(~0ull << 1) == 63);

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

    if(op == "countl_zero") {
      ull x;
      cin >> x;
      if(!cin) break;
      cout << countl_zero(x) << endl;

    } else if(op == "countr_zero") {
      ull x;
      cin >> x;
      if(!cin) break;
      cout << countr_zero(x) << endl;

    } else if(op == "popcount") {
      ull x;
      cin >> x;
      if(!cin) break;
      cout << popcount(x) << endl;

    } else if(op == "floor_log2") {
      ull x;
      cin >> x;
      if(!cin) break;
      ull result = floor_log2(x);
      cout << result << endl;
      assert(result == floor(log2(x)));

    } else if(op == "ceil_log2") {
      ull x;
      cin >> x;
      if(!cin) break;
      ull result = ceil_log2(x);
      cout << result << endl;
      assert(result == ceil(log2(x)));

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
