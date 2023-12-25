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
#include <unordered_map>
#include <vector>

/*
 * Spamiętywana silnia w O(x)
 */
unordered_map<ll, vector<ll>> fac_mem;
ll const fac_skip = 1;
ll fac(ll x, ll mod) {
  assert(mod > 0 && x >= 0);
  if(mod == 1) {
    return 0;
  } else if(x == 0) {
    return 1;
  }

  auto i = min<int>(x / fac_skip, fac_mem[mod].size());
  auto result = i == 0 ? 1 : fac_mem[mod][i - 1];
  if(x / fac_skip - 1 >= fac_mem[mod].size()) {
    fac_mem[mod].resize(x / fac_skip);
  }
  for(auto i: v::iota(i * fac_skip + 1, x + 1)) {
    result = mod_mul(result, i, mod);
    if(i % fac_skip == 0) {
      fac_mem[mod][i / fac_skip - 1] = result;
    }
  }
  return result;
}

/*
 * Zwyklejsza silnia w O(n)
 */
template<class Z>
struct Fac {
  vector<Z> fac, inv_fac;

  Fac(int n): fac(n + 1), inv_fac(n + 1) {
    fac[0] = 1;
    for(auto i: v::iota(1, n + 1)) {
      fac[i] = fac[i - 1] * i;
    }
    inv_fac[n] = fac[n].inv();
    for(auto i: v::iota(1, n + 1) | v::reverse) {
      inv_fac[i - 1] = inv_fac[i] * i;
    }
  }

  Z operator()(int x) const {
    return fac[x];
  }
  Z inv(int x) const {
    return inv_fac[x];
  }
};

/*
 * Symbol Newtona -
 *  Liczba k-elementowych podzbiorów n-elementowego zbioru w O(n + log mod)
 */
ll choose_fac(int n, int k, ll mod) {
  assert(n >= 0 && mod > 0);
  if(k < 0 || k > n) {
    return 0;
  }
  auto a = fac(n, mod);
  auto b = mod_inv(fac(n - k, mod), mod);
  auto c = mod_inv(fac(k, mod), mod);
  assert(b && c);
  return mod_mul(mod_mul(a, *b, mod), *c, mod);
}

/*
 * Symbol Newtona -
 *   Liczba k-elementowych podzbiorów n-elementowego zbioru w O(min(k, n - k) log mod)
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
  for(auto i: v::iota(1, k + 1)) {
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
  for(auto i: v::iota(2, n + 1)) {
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
  for(auto shift: v::iota(0, n)) {
    result += mod_pow(k, gcd(shift, n), mod);
    if(result >= mod) {
      result -= mod;
    }
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
  auto result = choose(2 * n, n, mod) - choose(2 * n, n + 1, mod);
  if(result < 0) {
    result += mod;
  }
  return result;
}
