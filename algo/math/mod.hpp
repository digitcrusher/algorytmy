/*
 * Arytmetyka modularna - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/ext_euclid.hpp"
#include <iostream>

/*
 * Normalizuje x do przedziału [0, mod) z zachowaniem x' = x % mod.
 */
ll norm_mod(ll x, ll mod) {
  assert(mod > 0);
  x %= mod;
  if(x < 0) {
    x += mod;
  }
  return x;
}

/*
 * Iteratywne potęgowanie modularne w O(log b)
 */
ll mod_pow(ll a, ll b, ll mod) {
  assert(mod > 0 && b >= 0);
  ll result = 1;
  while(b > 0) {
    if(b % 2 != 0) {
      result = result * (i128) a % mod;
    }
    a = a * (i128) a % mod;
    b /= 2;
  }
  if(result < 0) {
    result += mod;
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
optional<ll> mod_inv(ll x, ll mod) {
  assert(mod > 0);
  auto gcd = ext_euclid(x, mod);
  if(gcd.gcd != 1) {
    return nullopt;
  }
  return norm_mod(gcd.x, mod);
}

/*
 * Struktura ułatwiająca pracę z arytmetyką modularną
 */
template<ll _mod, bool is_mod_prime = false>
struct Z {
  static constexpr auto mod = _mod;
  static_assert(mod > 0);

  Z() {}
  Z(ll val): val(norm_mod(val, mod)) {}
  static Z unsafe(ll val) {
    Z result;
    result.val = val;
    return result;
  }

  explicit operator ll() const {
    return val;
  }
  bool operator==(Z other) const {
    return val == other.val;
  }
  bool operator!=(Z other) const {
    return !(*this == other);
  }

  Z operator+(Z other) const {
    return unsafe((val + other.val) % mod);
  }
  Z operator-(Z other) const {
    auto result = val - other.val;
    if(result < 0) {
      result += mod;
    }
    return unsafe(result);
  }
  Z operator*(Z other) const {
    return unsafe(val * (i128) other.val % mod);
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
    return unsafe(mod_pow(val, exp, mod));
  }
  Z inv() const {
    auto result = is_mod_prime ? mod_inv_prime(val, mod) : mod_inv(val, mod);
    assert(result);
    return unsafe(*result);
  }

private:
  ll val;
};

template<auto... A>
ostream& operator<<(ostream &stream, Z<A...> num) {
  return stream << (ll) num;
}
template<auto... A>
istream& operator>>(istream &stream, Z<A...> &num) {
  ll val;
  stream >> val;
  num = val;
  return stream;
}
template<auto... A>
struct std::hash<Z<A...>> {
  size_t operator()(Z<A...> const& num) const {
    return hash<ll>()((ll) num);
  }
};
