/*
 * Równania diofantyczne - digitcrusher/algorytmy
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

struct LinDiophantineSoln {
  ll x, y;
  ll a, b;
  ll gcd_ab;

  /*
   * Zwraca kolejne rozwiązanie równania diofantycznego.
   */
  LinDiophantineSoln shift_soln(int step) {
    return {
      x + b / gcd_ab * step,
      y - a / gcd_ab * step,
      a, b,
      gcd_ab
    };
  }
};
/*
 * Znajduje rozwiązanie równania diofantycznego ax + by = c
 * i, co za tym idzie, wszystkie rozwiązania.
 */
optional<LinDiophantineSoln> solve_lin_diophantine(ll a, ll b, ll c) {
  auto gcd = ext_euclid(a, b);
  if(c % gcd.gcd != 0) {
    return nullopt;
  }
  return LinDiophantineSoln{
    c / gcd.gcd * gcd.x,
    c / gcd.gcd * gcd.y,
    a, b,
    gcd.gcd,
  };
}
