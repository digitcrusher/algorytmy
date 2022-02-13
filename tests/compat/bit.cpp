#include "compat/bit.hpp"
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

  while(true) {
    string op;
    ull a;
    cin >> op >> a;
    if(!cin) break;
    if(op == "countl_zero") {
      cout << countl_zero(a) << endl;
    } else if(op == "countr_zero") {
      cout << countr_zero(a) << endl;
    } else if(op == "popcount") {
      cout << popcount(a) << endl;
    }
  }
}
