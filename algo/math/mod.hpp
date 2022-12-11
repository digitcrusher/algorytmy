/*
 * Arytmetyka modularna - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/ext_euclid.hpp"
#include <climits>
#include <optional>
#include <unordered_map>
#include <vector>

/*
 * Normalizuje x do przedziału [0, mod) z zachowaniem x' = x % mod.
 */
ll norm_mod(ll x, ll mod) {
  if(0 <= x && x < mod) {
    return x;
  }
  assert(mod > 0);
  x %= mod;
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

  if(b == 0) {
    return 0;
  } else if((a >= 0 && a <= LLONG_MAX / b) || (a < 0 && a >= LLONG_MIN / b)) {
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
 * Odwrotność modularna w O(log x) - x * mod_inv(x, mod) % mod = 1
 */
optional<ll> mod_inv(ll x, ll mod) {
  assert(mod > 0);
  auto gcd = ext_euclid(x, mod);
  if(gcd.gcd != 1) {
    return nullopt;
  }
  return norm_mod(gcd.x, mod);
}

/*
 * Odwrotność modularna dla dzielników będących
 * liczbami pierwszymi w O(log prime_mod)
 */
optional<ll> mod_inv_prime(ll x, ll prime_mod) {
  assert(prime_mod >= 2);
  if(x % prime_mod == 0) {
    return nullopt;
  }
  return mod_pow(x, prime_mod - 2, prime_mod); // z małego twierdzenia Fermata
}

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

  int i = min<int>(x / fac_skip, fac_mem[mod].size());
  ll result = i == 0 ? 1 : fac_mem[mod][i - 1];
  if(x / fac_skip - 1 >= fac_mem[mod].size()) {
    fac_mem[mod].resize(x / fac_skip);
  }
  for(i = i * fac_skip + 1; i <= x; i++) {
    result = mod_mul(result, i, mod);
    if(i % fac_skip == 0) {
      fac_mem[mod][i / fac_skip - 1] = result;
    }
  }
  return result;
}

/*
 * Struktura ułatwiająca pracę z arytmetyką modularną
 */
template<ll mod>
struct Z {
  ll val;

  Z(ll val): val(norm_mod(val, mod)) {}

  operator ll() const {
    return val;
  }

  Z operator+(Z other) const {
    return (val + other.val) % mod;
  }
  Z operator-(Z other) const {
    return norm_mod(val - other.val, mod);
  }
  Z operator*(Z other) const {
    return mod_mul(val, other.val, mod);
  }

  Z& operator+=(Z other) {
    return *this = *this + other;
  }
  Z& operator-=(Z other) {
    return *this = *this - other;
  }
  Z& operator*=(Z other) {
    return *this = *this * other;
  }

  Z pow(ll exp) const {
    return mod_pow(val, exp, mod);
  }
  Z inv() const {
    return mod_inv(val, mod);
  }
  Z inv_prime() const {
    return mod_inv_prime(val, mod);
  }
};
