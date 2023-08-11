#include "math/is_prime.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    ll x;
    cin >> x;

    cout << boolalpha << is_prime_miller_rabin(x) << endl;
  }
}
