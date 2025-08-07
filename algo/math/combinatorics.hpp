/*
 * Kombinatoryka - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/mod.hpp"

/*
 * Spamiętywana silnia w O(x + log mod) dla pierwszego
 * zapytania i O(1) dla kolejnych niewiększych od pierwszego
 */
template<class Z>
struct Fac {
  vector<Z> fac = {1}, inv_fac = {1};

  Z operator()(int x) {
    preload(x);
    return fac[x];
  }
  Z inv(int x) {
    preload(x);
    return inv_fac[x];
  }

  void preload(int n) {
    int old_n = fac.size() - 1;
    if(n <= old_n) return;
    fac.resize(n + 1);
    for(auto i: v::iota(old_n + 1, n + 1)) {
      fac[i] = fac[i - 1] * i;
    }
    inv_fac.resize(n + 1);
    inv_fac[n] = fac[n].inv();
    for(auto i: v::iota(old_n + 1, n + 1) | v::reverse) {
      inv_fac[i - 1] = inv_fac[i] * i;
    }
  }
};

/*
 * Symbol Newtona - liczba k-elementowych podzbiorów n-elementowego zbioru
 */
auto choose(int n, int k, auto &fac) {
  return 0 <= k && k <= n ? fac(n) * fac.inv(n - k) * fac.inv(k) : 0;
}

/*
 * Liczba sposobów na wsadzenie n nierozróżnialnych elementów do k różnych zbiorów
 */
auto any_in_uniq(int n, int k, auto &fac) {
  return choose(n + k - 1, k - 1, fac);
}

/*
 * Liczba sposobów na wsadzenie n różnych elementów do k różnych zbiorów
 */
auto uniq_in_uniq(int n, int k, auto &fac) {
  return any_in_uniq(n, k, fac) * fac(n);
}

/*
 * Liczby Catalana - m.in. liczba poprawnych nawiasowań długości 2n
 */
auto catalan(int n, auto &fac) {
  return choose(2 * n, n, fac) - choose(2 * n, n + 1, fac);
}

/*
 * Symbol Newtona -
 *   Liczba k-elementowych podzbiorów n-elementowego zbioru w O(min(k, n - k) log mod)
 */
template<class Z>
Z choose(int n, int k) {
  assert(n >= 0);
  if(k < 0 || k > n) {
    return 0;
  }
  Z result = 1;
  for(auto i: v::iota(1, min(k, n - k) + 1)) {
    result *= Z(i).inv() * (n - i + 1);
  }
  return result;
}

/*
 * Podsilnia - liczba permutacji bez punktu stałego
 */
template<class Z>
struct Subfac {
  vector<Z> subfac = {0, 1};

  Z operator()(int x) {
    preload(x);
    return subfac[x];
  }

  void preload(int n) {
    int old_n = subfac.size() - 1;
    if(n <= old_n) return;
    subfac.resize(n + 1);
    for(auto i: v::iota(old_n + 1, n + 1)) {
      subfac[i] = (subfac[i - 1] + subfac[i - 2]) * (i - 1);
    }
  }
};

/*
 * Klasyczne zastosowanie lematu Burnside'a do zliczenia wszystkich
 * cyklicznych ciągów długości n zawierających wartości od 1 do k
 */
template<class Z>
Z burnside(int n, int k) {
  Z result = 0;
  for(auto shift: v::iota(0, n)) {
    result += Z(k).pow(gcd(shift, n));
  }
  return result * Z(n).inv();
}

/*
 * Spamiętywana silnia z przeskokami w O(x + log mod) dla pierwszego
 * zapytania i O(skip) dla kolejnych niewiększych od pierwszego
 */
template<class Z>
struct SkipFac {
  vector<Z> fac = {1}, inv_fac = {1};
  ll skip;

  SkipFac(ll skip): skip(skip) {}

  Z operator()(ll x) {
    preload(x);
    auto init = x / skip;
    auto result = fac[init];
    for(auto i: v::iota(skip * init + 1, x + 1)) {
      result *= i;
    }
    return result;
  }
  Z inv(ll x) {
    preload(x);
    auto init = (x + skip - 1) / skip;
    auto result = inv_fac[init];
    for(auto i: v::iota(x + 1, skip * init + 1)) {
      result *= i;
    }
    return result;
  }

  void preload(ll x) {
    int n = (x + skip - 1) / skip, old_n = fac.size() - 1;
    if(n <= old_n) return;
    fac.resize(n + 1);
    for(auto i: v::iota(old_n + 1, n + 1)) {
      fac[i] = fac[i - 1];
      for(auto j: v::iota(0, skip)) {
        fac[i] *= skip * i - j;
      }
    }
    inv_fac.resize(n + 1);
    inv_fac[n] = fac[n].inv();
    for(auto i: v::iota(old_n + 1, n + 1) | v::reverse) {
      inv_fac[i - 1] = inv_fac[i];
      for(auto j: v::iota(0, skip)) {
        inv_fac[i - 1] *= skip * i - j;
      }
    }
  }
};
