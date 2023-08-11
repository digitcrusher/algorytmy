#include "math/sieve.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int lim;
    cin >> lim;

    auto result = sieve_euler(lim);
    cout << result.is_prime << endl;
    cout << result.primes << endl;
    cout << result.smallest_factor << endl;

    auto eratosthenes = sieve_eratosthenes(lim);
    assert(result.is_prime == eratosthenes.is_prime);
    assert(result.primes == eratosthenes.primes);
    assert(result.smallest_factor == eratosthenes.smallest_factor);
  }
}
