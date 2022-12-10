#include "math/is_prime.hpp"
#include <iostream>

int main() {
  while(true) {
    ll x;
    cin >> x;
    if(!cin) break;
    cout << boolalpha << is_prime_miller_rabin(x) << endl;
  }
}
