/*
 * Logarytm dyskretny - digitcrusher/algorytmy
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
#include <cmath>
#include <unordered_map>

/*
 * Logarytm dyskretny -
 *   Znajduje najmniejsze dodatnie x, takie że k * pow(a, x) % mod = b % mod,
 *   w O(sqrt(mod)). Rozpatrzenie przypadku gdy x = 0 jest trywialne, dlatego
 *   nie jest on tutaj uwzględniony.
 */
template<class Z>
optional<ll> discrete_log(Z _a, Z _b, Z _k = 1) {
  auto a = (ll) _a, b = (ll) _b, k = (ll) _k, mod = Z::mod;

  ll g, off = 0;
  while((g = gcd(a, mod)) > 1) {
    if(b == k && off != 0) {
      return off;
    }
    if(a == 0 && b == 0) {
      return off + 1;
    }
    if(b % g != 0) {
      return nullopt;
    }
    b /= g;
    mod /= g;
    k = k * (i128) (a / g) % mod;
    off++;
  }

  // Rozwiązujemy logarytm dyskretny dla a i mod wspólnie pierwszych

  ll n = ceil(sqrt(mod));
  auto a_pow_n = mod_pow(a, n, mod);

  unordered_map<ll, ll> qs;
  auto curr = b;
  for(auto q: v::iota(0, n)) {
    qs[curr] = q;
    curr = curr * (i128) a % mod;
  }

  curr = k;
  for(auto p: v::iota(1, n + 1)) {
    curr = curr * (i128) a_pow_n % mod;
    if(qs.count(curr) != 0) {
      auto ans = n * p - qs[curr] + off;
      if(ans != 0) {
        return ans;
      }
    }
  }

  return nullopt;
}
