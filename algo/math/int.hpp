/*
 * Różne operacje na liczbach całkowitych - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <bit>
#include <limits>

/*
 * Zwraca wykładnik największej potęgi dwójki mniejszej lub równej x.
 */
int floor_log2(ull x) {
  assert(x != 0);
  return numeric_limits<ull>::digits - countl_zero(x) - 1;
}

/*
 * Zwraca wykładnik najmniejszej potęgi dwójki większej lub równej x.
 */
int ceil_log2(ull x) {
  assert(x != 0);
  return numeric_limits<ull>::digits - countl_zero(x - 1);
}

/*
 * Dzielenie z zaokrągleniem w dół
 */
ll floor_div(ll a, ll b) {
  if(b < 0) {
    a = -a;
    b = -b;
  }
  return a >= 0 ? a / b : (a - b + 1) / b;
}

/*
 * Dzielenie z zaokrągleniem w górę
 */
ll ceil_div(ll a, ll b) {
  if(b < 0) {
    a = -a;
    b = -b;
  }
  return a >= 0 ? (a + b - 1) / b : a / b;
}

/*
 * Iteratywne potęgowanie w O(log b).
 */
ll fast_pow(ll a, ll b) {
  assert(b >= 0);
  ll result = 1;
  while(b > 0) {
    if(b % 2 == 1) {
      result = result * a;
    }
    a = a * a;
    b /= 2;
  }
  return result;
}

/*
 * Oblicza leksykograficznie następną permutacje bitów.
 */
ull next_perm(ull x) {
  // Formuła zapożyczona z https://graphics.stanford.edu/~seander/bithacks.html
  ull t = x | (x - 1);
  return (t + 1) | (((~t & -~t) - 1) >> (countr_zero(x) + 1));
}
