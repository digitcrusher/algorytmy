#include "math/sieve.hpp"
#include <iostream>

int main() {
  while(true) {
    int lim;
    cin >> lim;
    if(!cin) break;

    Sieve sieve = sieve_euler(lim);
    for(bool i: sieve.is_prime) {
      cout << i << " ";
    }
    cout << endl;
    for(int i: sieve.primes) {
      cout << i << " ";
    }
    cout << endl;
    for(int i: sieve.smallest_factor) {
      cout << i << " ";
    }
    cout << endl;

    Sieve eratosthenes = sieve_eratosthenes(lim);
    assert(sieve.is_prime == eratosthenes.is_prime);
    assert(sieve.primes == eratosthenes.primes);
    assert(sieve.smallest_factor == eratosthenes.smallest_factor);
  }
}
