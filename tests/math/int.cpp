#include "math/int.hpp"
#include "iostream.hpp"

int main() {
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

  while(cin) {
    string op;
    cin >> op;

    if(op == "floor_log2") {
      ull x;
      cin >> x;

      auto result = floor_log2(x);
      cout << result << endl;
      assert(result == floor(log2(x)));

    } else if(op == "ceil_log2") {
      ull x;
      cin >> x;

      auto result = ceil_log2(x);
      cout << result << endl;
      assert(result == ceil(log2(x)));

    } else if(op == "floor_div") {
      ll a, b;
      cin >> a >> b;

      auto result = floor_div(a, b);
      cout << result << endl;
      assert(result == floor((ld) a / b));

    } else if(op == "ceil_div") {
      ll a, b;
      cin >> a >> b;

      auto result = ceil_div(a, b);
      cout << result << endl;
      assert(result == ceil((ld) a / b));

    } else if(op == "fast_pow") {
      ll a, b;
      cin >> a >> b;

      cout << fast_pow(a, b) << endl;

    } else if(op == "next_perm") {
      ull x;
      cin >> x;

      cout << next_perm(x) << endl;
    }
  }
}
