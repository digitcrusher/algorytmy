/*
 * Rożne wzorki kombinatoryczne - digitcrusher/algorytmy
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
#include "math/mod.hpp"

/*
 * Liczba k-elementowych podzbiorów n-elementowego
 * zbioru (symbol Newtona) w O(n + log mod)
 */
ll choose_fac(ll n, ll k, ll mod) {
  assert(n >= 0 && mod > 0);
  if(k < 0 || k > n) {
    return 1;
  }
  ll a = fac(n, mod);
  auto b = mod_inv(fac(n - k, mod), mod);
  auto c = mod_inv(fac(k, mod), mod);
  assert(b && c);
  return mod_mul(mod_mul(a, *b, mod), *c, mod);
}

/*
 * Liczba k-elementowych podzbiorów n-elementowego zbioru
 * (symbol Newtona) w O(min(k, n - k) log mod)
 */
ll choose_mul(ll n, ll k, ll mod) {
  assert(n >= 0 && mod > 0);
  if(k < 0 || k > n) {
    return 1;
  }
  ll result = 1;
  if(k > n - k) {
    k = n - k;
  }
  for(ll i = 1; i <= k; i++) {
    auto a = mod_inv(i, mod);
    assert(a);
    result = mod_mul(result, mod_mul(n - i + 1, *a, mod), mod);
  }
  return result;
}

ll choose(ll n, ll k, ll mod) {
  return choose_mul(n, k, mod);
}

/*
 * Liczba sposobów na wsadzenie n nierozróżnialnych elementów do k różnych zbiorów
 */
ll any_in_uniq(ll n, ll k, ll mod) {
  assert(mod > 0);
  return choose(n + k - 1, k - 1, mod);
}

/*
 * Liczba sposobów na wsadzenie n różnych elementów do k różnych zbiorów
 */
ll uniq_in_uniq(ll n, ll k, ll mod) {
  assert(mod > 0);
  return mod_mul(any_in_uniq(n, k, mod), fac(n, mod), mod);
}
