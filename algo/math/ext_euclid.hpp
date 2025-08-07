/*
 * Rozszerzony algorytm Euklidesa - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"

/*
 * Rozszerzony algorytm Euklidesa -
 *   Znajduje NWD oraz współczynniki Bézouta liczb a i b w O(log min(a, b)),
 *   czyli jedno z rozwiązań dla równania diofantycznego ax + by = NWD(a, b)
 *   i, co za tym idzie, wszystkie rozwiązania.
 */
struct ExtEuclid {
  ll gcd;
  ll x, y;
  ll a, b;

  /*
   * Zwraca kolejne współczynniki Bézouta dla a i b.
   */
  ExtEuclid shift(int step) const {
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
ExtEuclid ext_euclid(ll a, ll b) {
  auto internal = Y([&](auto &self, ll a, ll b) -> ExtEuclid {
    if(b == 0) {
      return {a, 1, 0, a, b};
    }
    auto sub = self(b, a % b);
    return {
      sub.gcd,
      sub.y,
      sub.x - a / b * sub.y,
      a, b
    };
  });
  auto result = internal(abs(a), abs(b));
  if(a < 0) {
    result.x = -result.x;
  }
  if(b < 0) {
    result.y = -result.y;
  }
  return result;
}
#define EXT_EUCLID // dla math/mod.hpp
