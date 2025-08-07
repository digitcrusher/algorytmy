/*
 * Różne operacje na liczbach całkowitych - digitcrusher/algorytmy
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
 * Iteratywne potęgowanie w O(log b)
 */
ll fast_pow(ll a, ll b) {
  assert(b >= 0);
  ll result = 1;
  while(b > 0) {
    if(b % 2 != 0) {
      result *= a;
    }
    a *= a;
    b /= 2;
  }
  return result;
}

/*
 * Leksykograficznie następna permutacja bitów
 */
ull next_perm(ull x) {
  // Formuła zapożyczona z https://graphics.stanford.edu/~seander/bithacks.html
  auto t = x | (x - 1);
  return (t + 1) | (((~t & -~t) - 1) >> (countr_zero(x) + 1));
}

/*
 * Czy dwa przedziały się przecinają?
 */
template<class A>
bool do_intersect(A a1, A a2, A b1, A b2) {
  if(a1 > a2) {
    swap(a1, a2);
  }
  if(b1 > b2) {
    swap(b1, b2);
  }
  return !(a2 < b1 || b2 < a1);
}

/*
 * Czy punkt zawiera się w przedziale?
 */
template<class A>
bool do_intersect(A a1, A a2, A b) {
  if(a1 > a2) {
    swap(a1, a2);
  }
  return a1 <= b && b <= a2;
}

/*
 * Czy przedział a zawiera się w przedziale b?
 */
template<class A>
bool is_in(A a1, A a2, A b1, A b2) {
  if(a1 > a2) {
    swap(a1, a2);
  }
  if(b1 > b2) {
    swap(b1, b2);
  }
  return b1 <= a1 && a2 <= b2;
}
