/*
 * Transformacja liczbowo-teoretyczna - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/eulers_phi.hpp"
#include "math/factor.hpp"
#include "math/int.hpp"
#include "math/mod.hpp"
#include "math/primitive_root.hpp"
#include <vector>

/*
 * Transformacja liczbowo-teoretyczna (NTT) -
 *   Oblicza modularną dyskretną transformatę Fouriera lub jej odwrotność
 *   dla wielomianu o stopniu będącym potęgą dwójki w O(n log n).
 */
void ntt(vector<ll> &poly, ll mod, bool should_invert = false, ll omega = -1, ll two_inv = -1) {
  int const n = poly.size();
  if(n == 1) return;
  assert(popcount((uint) n) == 1);

  if(omega == -1) {
    auto totient = eulers_phi(mod, factor_pollard_rho(mod));
    assert(totient % n == 0);
    omega = mod_pow(*primitive_root(mod), totient / n, mod);
    if(should_invert) {
      omega = *mod_inv(omega, mod);
    }
  }
  if(two_inv == -1) {
    two_inv = *mod_inv(2, mod);
  }

  vector<ll> a(n / 2), b(n / 2);
  for(auto i: v::iota(0, n / 2)) {
    a[i] = poly[2 * i];
    b[i] = poly[2 * i + 1];
  }
  ntt(a, mod, should_invert, mod_mul(omega, omega, mod), two_inv);
  ntt(b, mod, should_invert, mod_mul(omega, omega, mod), two_inv);

  ll x = 1;
  for(auto i: v::iota(0, n / 2)) {
    poly[i] = a[i] + mod_mul(x, b[i], mod);
    if(poly[i] >= mod) {
      poly[i] -= mod;
    }
    poly[i + n / 2] = a[i] - mod_mul(x, b[i], mod);
    if(poly[i + n / 2] < 0) {
      poly[i + n / 2] += mod;
    }
    if(should_invert) {
      poly[i] = mod_mul(poly[i], two_inv, mod);
      poly[i + n / 2] = mod_mul(poly[i + n / 2], two_inv, mod);
    }
    x = mod_mul(x, omega, mod);
  }
}

/*
 * Mnoży dwa wielomiany z użyciem NTT w O((a + b) log (a + b)).
 */
void mul(vector<ll> &a, vector<ll> b, ll mod) {
  int const n = a.size() + b.size() - 1;
  int const m = 1u << ceil_log2(n);
  a.resize(m);
  b.resize(m);

  ntt(a, mod);
  ntt(b, mod);
  for(auto i: v::iota(0, m)) {
    a[i] = mod_mul(a[i], b[i], mod);
  }
  ntt(a, mod, true);

  a.resize(n);
}
