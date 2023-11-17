/*
 * Test pierwszości - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/int.hpp"
#include "math/mod.hpp"
#include "math/sieve.hpp"
#include <vector>

/*
 * Pierwszość liczby można sprawdzać za pomocą sita.
 */
bool is_prime_sieve(int x, Sieve const& sieve) {
  return sieve.is_prime[x];
}

/*
 * Test pierwszości Millera-Rabina -
 *   Sprawdza czy liczba mieszcząca się w 64 bitach jest pierwsza w O(log x).
 */
bool is_prime_miller_rabin(ll x) {
  if(x <= 1) {
    return false;
  }

  auto odd = (x - 1) >> countr_zero(x - 1ull);

  for(auto base: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if(x == base) {
      return true;
    }
    auto is_composite = mod_pow(base, odd, x) != 1;
    for(auto i = odd; i < x - 1 && is_composite; i *= 2) {
      if(mod_pow(base, i, x) == x - 1) {
        is_composite = false;
      }
    }
    if(is_composite) {
      return false;
    }
  }
  return true;
}
