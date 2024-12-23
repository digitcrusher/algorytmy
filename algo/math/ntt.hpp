/*
 * Transformacja liczbowo-teoretyczna - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
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

/*
 * Transformacja liczbowo-teoretyczna (NTT) -
 *   Oblicza modularną dyskretną transformatę Fouriera lub jej odwrotność
 *   dla wielomianu o stopniu będącym potęgą dwójki w O(n log n).
 */
template<class Z>
struct NTT {
  Z root;
  ll mod_totient;

  NTT() {
    auto maybe_root = primitive_root(Z::mod);
    assert(maybe_root);
    root = *maybe_root;
    mod_totient = eulers_phi(Z::mod, factor_pollard_rho(Z::mod));
  }

  void operator()(vector<Z> &poly, bool should_invert = false) const {
    int n = poly.size();
    assert(popcount<uint>(n) == 1);

    auto conquer = Y([&](auto &self, vector<Z> &poly, Z omega) {
      int n = poly.size();
      if(n == 1) return;

      vector<Z> a(n / 2), b(n / 2);
      for(auto i: v::iota(0, n / 2)) {
        a[i] = poly[2 * i];
        b[i] = poly[2 * i + 1];
      }
      self(a, omega * omega);
      self(b, omega * omega);

      Z x = 1;
      for(auto i: v::iota(0, n / 2)) {
        poly[i] = a[i] + x * b[i];
        poly[i + n / 2] = a[i] - x * b[i];
        if(should_invert) {
          poly[i] = poly[i] * Z(2).inv();
          poly[i + n / 2] = poly[i + n / 2] * Z(2).inv();
        }
        x *= omega;
      }
    });

    assert(mod_totient % n == 0);
    auto omega = root.pow(mod_totient / n);
    if(should_invert) {
      omega = omega.inv();
    }
    conquer(poly, omega);
  }

  /*
   * Mnoży dwa wielomiany w O((a + b) log (a + b)).
   */
  void conv(vector<Z> &a, vector<Z> b) const {
    int n = a.size() + b.size() - 1;
    int m = 1u << ceil_log2(n);
    a.resize(m);
    b.resize(m);

    (*this)(a);
    (*this)(b);
    for(auto i: v::iota(0, m)) {
      a[i] *= b[i];
    }
    (*this)(a, true);

    a.resize(n);
  }
};
