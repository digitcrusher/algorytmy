/*
 * Konwolucje - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <complex>

using cld = complex<long double>;

/*
 * Szybka transformacja Fouriera (FFT) -
 *   Oblicza dyskretną transformatę Fouriera lub jej odwrotność
 *   dla wielomianu o stopniu będącym potęgą dwójki w O(n log n).
 */
void fft(vector<cld> &poly, bool should_invert = false) {
  int n = poly.size();
  if(n == 1) return;
  assert(has_single_bit<uint>(n));

  vector<cld> a(n / 2), b(n / 2);
  for(auto i: v::iota(0, n / 2)) {
    a[i] = poly[2 * i];
    b[i] = poly[2 * i + 1];
  }
  fft(a, should_invert);
  fft(b, should_invert);

  auto omega = polar<ld>(1, 2 * numbers::pi / n * (should_invert ? -1 : 1));
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
void conv(vector<cld> &a, vector<cld> b) {
  int n = a.size() + b.size() - 1;
  int m = bit_ceil<uint>(n);
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

/*
 * Szybka transformacja Walsha-Hadamarda (FWHT) o podstawie 3 -
 *   Oblicza transformatę Walsha-Hadamarda lub jej odwrotność dla wielomianu
 *   k zmiennych o stopniu 3 w O(k * 3^k).
 */
void fwht3(vector<cld> &poly, bool should_invert = false) {
  int n = poly.size();
  auto omega = polar<ld>(1, 2 * numbers::pi / 3 * (should_invert ? -1 : 1));
  auto omega2 = omega * omega;
  for(auto size = 1; size < n; size *= 3) {
    for(auto i = 0; i < n; i += 3 * size) {
      for(auto j: v::iota(i, i + size)) {
        auto a = poly[j], b = poly[j + size], c = poly[j + 2 * size];
        poly[j] = a + b + c;
        poly[j + size] = a + b * omega + c * omega2;
        poly[j + 2 * size] = a + b * omega2 + c * omega;
        if(should_invert) {
          poly[j] /= 3;
          poly[j + size] /= 3;
          poly[j + 2 * size] /= 3;
        }
      }
    }
  }
}

/*
 * Konwolucja XOR o podstawie 3 -
 *   Mnoży dwa wielomiany z użyciem FWHT w O(max(a, b) log max(a, b)),
 *   ale potęgi się XORują w systemie trójkowym zamiast dodawać.
 */
void xor3_conv(vector<cld> &a, vector<cld> b) {
  int n = max(a.size(), b.size());
  auto m = 1;
  while(m < n) {
    m *= 3;
  }
  a.resize(m);
  b.resize(m);

  fwht3(a);
  fwht3(b);
  for(auto i: v::iota(0, m)) {
    a[i] *= b[i];
  }
  fwht3(a, true);
}
