/*
 * Arytmetyka modularna - digitcrusher/algorytmy
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
#include "math/ext_euclid.hpp"
#include <climits>
#include <optional>
#include <unordered_map>
#include <vector>

/*
 * Normalizuje a do przedziału [0, mod) z zachowaniem a' = a % mod.
 */
ll norm_mod(ll a, ll mod) {
  assert(mod > 0);
  ll x = a % mod;
  return x + (x < 0 ? mod : 0);
}

/*
 * Iteratywne mnożenie modularne w O(log b) lub O(1)
 */
#ifdef __SIZEOF_INT128__
ll mod_mul(ll a, ll b, ll mod) {
  assert(mod > 0);
  ll result = (__int128_t) a * b % mod;
  if(result < 0) {
    result += mod;
  }
  return result;
}
#else
ll mod_mul(ll a, ll b, ll mod) {
  assert(mod > 0);
  a %= mod;
  b %= mod;
  if(b < 0) {
    a = -a;
    b = -b;
  }

  if((a >= 0 && a <= LLONG_MAX / b) || (a < 0 && a >= LLONG_MIN / b)) {
    return norm_mod(a * b, mod);
  }

  ll result = 0;
  while(b > 0) {
    if(b % 2 == 1) {
      result = (result + a) % mod;
    }
    a = a * 2 % mod;
    b /= 2;
  }
  if(result < 0) {
    result += mod;
  }
  return result;
}
#endif

/*
 * Iteratywne potęgowanie modularne w O(log a * log b) lub O(log b)
 */
ll mod_pow(ll a, ll b, ll mod) {
  assert(mod > 0 && b >= 0);
  ll result = 1;
  while(b > 0) {
    if(b % 2 == 1) {
      result = mod_mul(result, a, mod);
    }
    a = mod_mul(a, a, mod);
    b /= 2;
  }
  return result;
}

/*
 * Odwrotność modularna w O(log a) - a * mod_inv(a, mod) % mod = 1
 */
optional<ll> mod_inv(ll a, ll mod) {
  assert(mod > 0);
  auto gcd = ext_euclid(a, mod);
  if(gcd.gcd != 1) {
    return nullopt;
  }
  return norm_mod(gcd.x, mod);
}

/*
 * Odwrotność modularna dla dzielników będących
 * liczbami pierwszymi w O(log prime_mod)
 */
optional<ll> mod_inv_prime(ll a, ll prime_mod) {
  assert(prime_mod >= 2);
  if(a % prime_mod == 0) {
    return nullopt;
  }
  return mod_pow(a, prime_mod - 2, prime_mod); // z małego twierdzenia Fermata
}

/*
 * Spamiętywana silnia w O(a)
 */
unordered_map<ll, vector<ll>> fac_mem;
ll const fac_skip = 1;
ll fac(ll a, ll mod) {
  assert(mod > 0 && a >= 0);
  if(mod == 1) {
    return 0;
  } else if(a == 0) {
    return 1;
  }

  if(a % fac_skip == 0) {
    int i = a / fac_skip - 1;
    if(i >= fac_mem[mod].size()) {
      ll result = fac_mem[mod].empty() ? 1 : fac_mem[mod].back();
      ll b = fac_mem[mod].size() * fac_skip + 1;
      fac_mem[mod].resize(i + 1);

      for(; b <= a; b++) {
        result = mod_mul(result, b, mod);
        if(b % fac_skip == 0) {
          fac_mem[mod][b / fac_skip - 1] = result;
        }
      }
    }
    return fac_mem[mod][i];

  } else {
    int i = a / fac_skip - 1;
    ll result = i < 0 ? 1 : fac_mem[mod][i];
    for(ll b = (i + 1) * fac_skip + 1; b <= a; b++) {
      result = mod_mul(result, b, mod);
    }
    return result;
  }
}
