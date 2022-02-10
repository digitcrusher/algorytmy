/*
 * Sito Eratostenesa - digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include <vector>

/*
 * Sito Eratostenesa -
 *   Znajduje wszystkie liczby pierwsze mniejsze
 *   lub równe lim w O(lim log log lim).
 */
struct Sieve {
  vector<bool> is_prime;
  vector<ll> primes;
  vector<ll> smallest_factor; // Najmniejszy dzielnik pierwszy danej liczby
};
Sieve sieve_eratosthenes(ll lim) {
  assert(lim > 0);

  vector<bool> is_prime(lim + 1, true);
  is_prime[0] = false;
  is_prime[1] = false;
  vector<ll> primes;
  vector<ll> smallest_factor(lim + 1, -1);

  bool is_under_lim = true;
  for(ll i = 2; i <= lim; i += 2) {
    is_under_lim &= i * i <= lim;
    if(is_prime[i]) {
      primes.push_back(i);
      smallest_factor[i] = i;
      if(is_under_lim) {
        for(ll j = i * 2; j <= lim; j += i) {
          is_prime[j] = false;
          if(smallest_factor[j] == -1) {
            smallest_factor[j] = i;
          }
        }
      }
    }
    if(i == 2) i--;
  }

  return {is_prime, primes, smallest_factor};
}
