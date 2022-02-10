/*
 * Test pierwszości - digitcrusher/algorytmy
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
#include "compat/bit.hpp"
#include "math/mod.hpp"
#include "math/sieve.hpp"
#include <vector>

/*
 * Pierwszość liczby można sprawdzać za pomocą sita.
 */
bool is_prime_sieve(int n, Sieve const& sieve) {
  return sieve.is_prime[n];
}

/*
 * Test pierwszości Millera-Rabina
 */
bool is_prime_miller_rabin(ll n) {
  if(n < 2) {
    return false;
  }

  ll odd = (n - 1) >> countr_zero(n - 1);

  for(ll base: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if(n == base) {
      return true;
    }
    bool is_composite = true;
    if(mod_pow(base, odd, n) == 1) {
      is_composite = false;
    }
    for(ll j = odd; j < n - 1 && is_composite; j *= 2) {
      if(mod_pow(base, j, n) == n - 1) {
        is_composite = false;
      }
    }
    if(is_composite) {
      return false;
    }
  }
  return true;
}
