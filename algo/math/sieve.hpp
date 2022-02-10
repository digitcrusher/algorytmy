/*
 * Sita liczb pierwszych - digitcrusher/algorytmy
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

struct Sieve {
  vector<bool> is_prime;
  vector<int> primes;
  vector<int> smallest_factor; // Najmniejszy dzielnik pierwszy danej liczby
};

/*
 * Sito Eulera -
 *   Znajduje najmniejsze dzielniki pierwsze wszystkich liczb mniejszych lub
 *   równych lim i tym samym liczby pierwsze wsród nich w O(lim). Sito Eulera
 *   jest zwykle troszeczkę szybsze od sita Eratostenesa.
 */
Sieve sieve_euler(int lim) {
  assert(lim > 0);

  vector<bool> is_prime(lim + 1, false);
  vector<int> primes;
  vector<int> smallest_factor(lim + 1, -1);

  for(int i = 2; i <= lim; i++) {
    if(smallest_factor[i] == -1) {
      smallest_factor[i] = i;
      primes.push_back(i);
      is_prime[i] = true;
    }
    for(int prime: primes) {
      if(prime > smallest_factor[i] || prime * i > lim) break;
      smallest_factor[prime * i] = prime;
    }
  }

  return {is_prime, primes, smallest_factor};
}

/*
 * Sito Eratostenesa -
 *   Znajduje wszystkie liczby pierwsze mniejsze
 *   lub równe lim w O(lim log log lim).
 */
Sieve sieve_eratosthenes(int lim) {
  assert(lim > 0);

  vector<bool> is_prime(lim + 1, true);
  is_prime[0] = false;
  is_prime[1] = false;
  vector<int> primes;
  vector<int> smallest_factor(lim + 1, -1);

  bool is_under_lim = true;
  for(int i = 2; i <= lim; i += 2) {
    is_under_lim &= i * i <= lim;
    if(is_prime[i]) {
      if(is_under_lim) {
        for(int j = i * i; j <= lim; j += i) {
          is_prime[j] = false;
          if(smallest_factor[j] == -1) {
            smallest_factor[j] = i;
          }
        }
      }
      primes.push_back(i);
      smallest_factor[i] = i;
    }
    if(i == 2) {
      i--;
    }
  }

  return {is_prime, primes, smallest_factor};
}
