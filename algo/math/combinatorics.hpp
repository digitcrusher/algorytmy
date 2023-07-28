/*
 * Kombinatoryka - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/mod.hpp"
#include <numeric>
#include <vector>

/*
 * Symbol Newtona -
 *  liczba k-elementowych podzbiorów n-elementowego zbioru w O(n + log mod)
 */
ll choose_fac(int n, int k, ll mod) {
  assert(n >= 0 && mod > 0);
  if(k < 0 || k > n) {
    return 0;
  }
  ll a = fac(n, mod);
  auto b = mod_inv(fac(n - k, mod), mod);
  auto c = mod_inv(fac(k, mod), mod);
  assert(b && c);
  return mod_mul(mod_mul(a, *b, mod), *c, mod);
}

/*
 * Symbol Newtona -
 *   liczba k-elementowych podzbiorów n-elementowego zbioru w O(min(k, n - k) log mod)
 */
ll choose_mul(int n, int k, ll mod) {
  assert(n >= 0 && mod > 0);
  if(k < 0 || k > n) {
    return 0;
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

ll choose(int n, int k, ll mod) {
  return choose_mul(n, k, mod);
}

/*
 * Liczba sposobów na wsadzenie n nierozróżnialnych elementów do k różnych zbiorów
 */
ll any_in_uniq(int n, int k, ll mod) {
  assert(mod > 0);
  return choose(n + k - 1, k - 1, mod);
}

/*
 * Liczba sposobów na wsadzenie n różnych elementów do k różnych zbiorów
 */
ll uniq_in_uniq(int n, int k, ll mod) {
  assert(mod > 0);
  return mod_mul(any_in_uniq(n, k, mod), fac(n, mod), mod);
}

/*
 * Podsilnia - liczba permutacji bez punktu stałego
 */
ll subfac(int n, ll mod) {
  assert(mod > 0);
  vector<ll> result(max(n + 1, 2));
  result[0] = 1;
  result[1] = 0;
  for(int i = 2; i <= n; i++) {
    result[i] = mod_mul(i - 1, result[i - 1] + result[i - 2], mod);
  }
  return result[n];
}

/*
 * Klasyczne zastosowanie lematu Burnside'a do zliczenia wszystkich
 * cyklicznych ciągów długości n zawierających k możliwych wartości
 */
ll burnside(int n, int k, ll mod) {
  assert(mod > 0);
  ll result = 0;
  for(int shift = 0; shift < n; shift++) {
    result = norm_mod(result + mod_pow(k, gcd(shift, n), mod), mod);
  }
  auto inv_n = mod_inv(n, mod);
  assert(inv_n);
  return mod_mul(result, *inv_n, mod);
}

/*
 * Liczby Catalana - m.in. liczba poprawnych nawiasowań długości 2n
 */
ll catalan(int n, ll mod) {
  assert(mod > 0);
  return norm_mod(choose(2 * n, n, mod) - choose(2 * n, n + 1, mod), mod);
}
