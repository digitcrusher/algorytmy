#include "math/is_prime.hpp"
#include <iostream>

int main() {
  while(true) {
    ll n;
    cin >> n;
    if(!cin) break;
    cout << boolalpha << is_prime_miller_rabin(n) << endl;
  }
}
