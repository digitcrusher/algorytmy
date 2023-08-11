/*
 * Równania diofantyczne - digitcrusher/algorytmy
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
#include <optional>

/*
 * Znajduje rozwiązanie równania diofantycznego ax + by = c
 * w O(log min(a, b)) i, co za tym idzie, wszystkie rozwiązania.
 */
struct LinDiophantineSoln {
  ll x, y;
  ll a, b;
  ll gcd_ab;

  /*
   * Zwraca kolejne rozwiązanie równania diofantycznego.
   */
  LinDiophantineSoln shift(int step) {
    return {
      x + b / gcd_ab * step,
      y - a / gcd_ab * step,
      a, b,
      gcd_ab
    };
  }
};
optional<LinDiophantineSoln> solve_lin_diophantine(ll a, ll b, ll c) {
  auto gcd = ext_euclid(a, b);
  if(c % gcd.gcd != 0) {
    return nullopt;
  }
  return LinDiophantineSoln{
    c / gcd.gcd * gcd.x,
    c / gcd.gcd * gcd.y,
    a, b,
    gcd.gcd
  };
}
