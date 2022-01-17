/*
 * Różne operacje na liczbach całkowitych - digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include "compat/bit.hpp"
#include <limits>

ull floor_log2(ull a) {
  assert(a != 0);
  return numeric_limits<ull>::digits - countl_zero(a) - 1;
}

ull ceil_log2(ull a) {
  assert(a != 0);
  return numeric_limits<ull>::digits - countl_zero(a - 1);
}

ll floor_div(ll a, ll b) {
  if(b < 0) {
    a = -a;
    b = -b;
  }
  return a >= 0 ? a / b : (a - b + 1) / b;
}

ll ceil_div(ll a, ll b) {
  if(b < 0) {
    a = -a;
    b = -b;
  }
  return a >= 0 ? (a + b - 1) / b : a / b;
}
