/*
 * Logarytm dyskretny - digitcrusher/algorytmy
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
#include <cmath>
#include <numeric>
#include <optional>
#include <unordered_map>

/*
 * Logarytm dyskretny -
 *   Znajduje najmniejsze dodatnie x, takie że k * pow(a, x) % mod = b % mod,
 *   w O(sqrt(mod)). Rozpatrzenie przypadku gdy x = 0 jest trywialne, dlatego
 *   nie jest on tutaj uwzględniony.
 */
optional<ll> discrete_log(ll a, ll b, ll mod, ll k = 1) {
  a = norm_mod(a, mod);
  b = norm_mod(b, mod);
  k = norm_mod(k, mod);

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
    k = mod_mul(k, a / g, mod);
    off++;
  }

  // Rozwiązujemy logarytm dyskretny dla a i mod wspólnie pierwszych

  ll n = ceil(sqrt(mod));
  ll a_pow_n = mod_pow(a, n, mod);

  unordered_map<ll, ll> qs;
  ll curr = b;
  for(ll q = 0; q < n; q++) {
    qs[curr] = q;
    curr = mod_mul(curr, a, mod);
  }

  curr = k;
  for(ll p = 1; p <= n; p++) {
    curr = mod_mul(curr, a_pow_n, mod);
    if(qs.count(curr) != 0) {
      ll ans = norm_mod(mod_mul(n, p, mod) - qs[curr] + off, mod);
      if(ans != 0) {
        return ans;
      }
    }
  }

  return nullopt;
}
