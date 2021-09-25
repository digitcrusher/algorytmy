/*
 * Arytmetyka modularna - digitcrusher/algorytmy
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
#include "compat/optional.hpp"
#include "math/ext_euclid.hpp"

/*
 * Normalizuje a do przedziału [0, mod) z zachowaniem a' = a % mod.
 */
ll norm_mod(ll a, ll mod) {
  ll x = a % mod;
  return x + (x < 0 ? mod : 0);
}



/*
 * Iteratywne mnożenie i potęgowanie modularne
 */
ll mod_mul(ll a, ll b, ll mod) {
  ll result = 0;
  if(b < 0) {
    a = -a;
    b = -b;
  }
  while(b > 0) {
    if(b % 2 == 1) {
      result = (result + a) % mod;
    }
    a = a * 2 % mod;
    b /= 2;
  }
  return result;
}
ll mod_pow(ll a, ll b, ll mod) {
  assert(b >= 0);
  ll result = 1;
  while(b > 0) {
    if(b % 2 == 1) {
      result = result * a % mod;
    }
    a = a * a % mod;
    b /= 2;
  }
  return result;
}



/*
 * Odwrotność modularna - a * mod_inv(a, mod) % mod = 1 % mod
 */
optional<ll> mod_inv_ext_euclid(ll a, ll mod) {
  auto gcd = ext_euclid(a, mod);
  if(gcd.gcd != 1) {
    return nullopt;
  }
  return norm_mod(gcd.x, mod);
}
optional<ll> mod_inv(ll a, ll mod) {
  return mod_inv_ext_euclid(a, mod);
}



/*
 * Odwrotność modularna dla dzielników będących liczbami pierwszymi
 */
ll mod_inv_prime(ll a, ll prime_mod) {
  return mod_pow(a, prime_mod - 2, prime_mod); // z małego twierdzenia Fermata
}
