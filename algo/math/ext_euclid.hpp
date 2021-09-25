/*
 * Rozszerzony algorytm Euklidesa - digitcrusher/algorytmy
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
#include <cmath>
#include <stdexcept>

struct ExtEuclidResult {
  ll gcd;
  ll x, y;
  ll a, b;

  /*
   * Zwraca kolejne współczynniki Bézouta dla a i b.
   */
  ExtEuclidResult shift_coefs(int step) {
    if(gcd == 0) {
      throw std::runtime_error(
        "Dla NWD równego zero istnieje nieskończenie wiele współczynników."
      );
    }
    return {
      gcd,
      x + b / gcd * step,
      y - a / gcd * step,
      a, b
    };
  }
};
ExtEuclidResult internal_ext_euclid(ll a, ll b) {
  if(b == 0) {
    return {a, 1, 0, a, b};
  }
  auto sub = internal_ext_euclid(b, a % b);
  return {
    sub.gcd,
    sub.y,
    sub.x - a / b * sub.y,
    a, b
  };
}
/*
 * Rozszerzony algorytm Euklidesa -
 *   Znajduje NWD oraz współczynniki Bézouta liczb a i b,
 *   czyli jedno z rozwiązań dla równania diofantycznego ax + by = NWD(a, b)
 *   i, co za tym idzie, wszystkie rozwiązania.
 */
ExtEuclidResult ext_euclid(ll a, ll b) {
  auto result = internal_ext_euclid(abs(a), abs(b));
  if(a < 0) {
    result.x = -result.x;
  }
  if(b < 0) {
    result.y = -result.y;
  }
  return result;
}
