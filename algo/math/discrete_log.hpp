/*
 * Logarytm dyskretny - digitcrusher/algorytmy
 *
 * Copyright (c) 2021 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include "compat/numeric.hpp"
#include "compat/optional.hpp"
#include "math/mod.hpp"
#include <cmath>
#include <unordered_map>

/*
 * Logarytm dyskretny, dla a i mod wspólnie pierwszych
 *   Znajduje najmniejsze dodatnie x, takie że k * pow(a, x) % mod = b % mod
 */
optional<ll> discrete_log_coprime(ll a, ll b, ll mod, ll k = 1, ll ans_off = 0) {
  a = norm_mod(a, mod);
  b = norm_mod(b, mod);

  assert(gcd(a, mod) == 1);

  ll n = ceil(sqrt(mod));
  ll a_pow_n = mod_pow(a, n, mod);

  unordered_map<ll, ll> qs;
  ll curr = b;
  for(ll q = 0; q < n; q++) {
    qs[curr] = q;
    curr = curr * a % mod;
  }

  curr = k;
  for(ll p = 1; p <= n; p++) {
    curr = curr * a_pow_n % mod;
    if(qs.find(curr) != qs.end()) {
      ll ans = n * p - qs[curr] + ans_off;
      if(ans != 0) {
        return ans;
      }
    }
  }

  return nullopt;
}



/*
 * Logarytm dyskretny
 */
optional<ll> discrete_log(ll a, ll b, ll mod, ll k = 1) {
  ll g, off = 0;
  while((g = gcd(a, mod)) > 1) {
    if(b == k) {
      return off;
    }
    if(a % mod == 0 && b % mod == 0) {
      return off + 1;
    }
    if(b % g != 0) {
      return nullopt;
    }
    b /= g;
    mod /= g;
    k = k * (a / g) % mod;
    off++;
  }
  return discrete_log_coprime(a, b, mod, k, off);
}
