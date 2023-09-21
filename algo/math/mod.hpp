/*
 * Arytmetyka modularna - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/ext_euclid.hpp"
#include <climits>
#include <iostream>
#include <optional>

/*
 * Normalizuje x do przedziału [0, mod) z zachowaniem x' = x % mod.
 */
ll norm_mod(ll x, ll mod) {
  assert(mod > 0);
  if(0 <= x && x < mod) {
    return x;
  }
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
  a = norm_mod(a, mod);
  b = norm_mod(b, mod);

  if(b == 0) {
    return 0;
  } else if(a <= LLONG_MAX / b) {
    return norm_mod(a * b, mod);
  }

  ll result = 0;
  while(b > 0) {
    if(b % 2 != 0) {
      result += a;
      if(result >= mod) {
        result -= mod;
      }
    }
    a *= 2;
    if(a >= mod) {
      a -= mod;
    }
    b /= 2;
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
    if(b % 2 != 0) {
      result = mod_mul(result, a, mod);
    }
    a = mod_mul(a, a, mod);
    b /= 2;
  }
  return result;
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
 * Odwrotność modularna w O(log x) - x * mod_inv(x, mod) % mod = 1
 */
#ifdef ext_euclid
optional<ll> mod_inv(ll x, ll mod) {
  assert(mod > 0);
  auto gcd = ext_euclid(x, mod);
  if(gcd.gcd != 1) {
    return nullopt;
  }
  return norm_mod(gcd.x, mod);
}
#else
optional<ll> mod_inv(ll x, ll mod) {
  assert(false);
}
#endif

/*
 * Struktura ułatwiająca pracę z arytmetyką modularną
 */
template<ll mod, bool is_mod_prime = false>
struct Z {
  Z() {}
  Z(ll val): val(norm_mod(val, mod)) {}

  explicit operator ll() const {
    return val;
  }

  Z operator+(Z other) const {
    auto result = val + other.val;
    if(result >= mod) {
      result -= mod;
    }
    return result;
  }
  Z operator-(Z other) const {
    auto result = val - other.val;
    if(result < 0) {
      result += mod;
    }
    return result;
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
    return is_mod_prime ? *mod_inv_prime(val, mod) : *mod_inv(val, mod);
  }

private:
  ll val;
};

template<ll a, bool b>
ostream& operator<<(ostream &stream, Z<a, b> num) {
  return stream << (ll) num;
}
template<ll a, bool b>
istream& operator>>(istream &stream, Z<a, b> &num) {
  ll val;
  stream >> val;
  num = val;
  return stream;
}
