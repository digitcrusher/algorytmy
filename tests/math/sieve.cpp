#include "math/sieve.hpp"
#include <iostream>

int main() {
  while(true) {
    ll lim;
    cin >> lim;
    if(!cin) break;

    Sieve sieve = sieve_eratosthenes(lim);
    for(bool i: sieve.is_prime) {
      cout << i << " ";
    }
    cout << endl;
    for(ll i: sieve.primes) {
      cout << i << " ";
    }
    cout << endl;
    for(ll i: sieve.smallest_factor) {
      cout << i << " ";
    }
    cout << endl;
  }
}
