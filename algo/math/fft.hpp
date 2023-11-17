/*
 * Szybka transformacja Fouriera - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/int.hpp"
#include <complex>
#include <numbers>
#include <vector>

using cld = complex<long double>;

/*
 * Szybka transformacja Fouriera (FFT) -
 *   Oblicza dyskretną transformatę Fouriera lub jej odwrotność
 *   dla wielomianu o stopniu będącym potęgą dwójki w O(n log n).
 */
void fft(vector<cld> &poly, bool should_invert = false) {
  int const n = poly.size();
  if(n == 1) return;
  assert(popcount((uint) n) == 1);

  vector<cld> a(n / 2), b(n / 2);
  for(auto i: v::iota(0, n / 2)) {
    a[i] = poly[2 * i];
    b[i] = poly[2 * i + 1];
  }
  fft(a, should_invert);
  fft(b, should_invert);

  cld omega(cos(2 * numbers::pi / n), sin(2 * numbers::pi / n) * (should_invert ? -1 : 1));
  cld x = 1;
  for(auto i: v::iota(0, n / 2)) {
    poly[i] = a[i] + x * b[i];
    poly[i + n / 2] = a[i] - x * b[i];
    if(should_invert) {
      poly[i] /= 2;
      poly[i + n / 2] /= 2;
    }
    x *= omega;
  }
}

/*
 * Mnoży dwa wielomiany z użyciem FFT w O((a + b) log (a + b)).
 */
void mul(vector<cld> &a, vector<cld> b) {
  int const n = a.size() + b.size() - 1;
  int const m = 1u << ceil_log2(n);
  a.resize(m);
  b.resize(m);

  fft(a);
  fft(b);
  for(auto i: v::iota(0, m)) {
    a[i] *= b[i];
  }
  fft(a, true);

  a.resize(n);
}
