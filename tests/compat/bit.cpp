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
  assert(countl_zero((1ull << 63) - 1) == 1);
  assert(countl_zero(1ull << 63) == 0);
  assert(countl_zero(~0ull) == 0);

  assert(countl_zero(1) == 30);
  assert(countl_zero(1u) == 31);
  assert(countl_zero(1ll) == 62);

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
   * dla każdego z dwóch przypadków. Wszystkiego dowiedziałem się od "wreien" z
   * serwera Discord Together C & C++.
   */
}
