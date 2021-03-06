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
#include <limits>

#if defined(__GLIBCXX__) || defined(__GLIBCPP__)
namespace std {
  template<class A>
  int countl_zero(A a) {
    // Wyjaśnienie tego ifa znajduje się w tests/math/int.cpp
    int digit_diff = numeric_limits<ull>::digits - numeric_limits<A>::digits;
    return a == 0 ? numeric_limits<A>::digits : __builtin_clzll(a) - digit_diff;
  }
  template<class A>
  int countr_zero(A a) {
    return a == 0 ? numeric_limits<A>::digits : __builtin_ctzll(a);
  }
  template<class A>
  int popcount(A a) {
    return __builtin_popcountll(a);
  }
}
#else
# include <cmath>
namespace std {
  template<class A>
  int countl_zero(A a) {
    int result = numeric_limits<A>::digits;
    while(a > 0) {
      result--;
      a >>= 1;
    }
    return result;
  }
  template<class A>
  int countr_zero(A a) {
    return numeric_limits<A>::digits - countl_zero((a - 1) & ~a);
  }
  template<class A>
  int popcount(A a) {
    int result = 0;
    while(a > 0) {
      result++;
      a = a & (a - 1);
    }
    return result;
  }
}
#endif

/*
 * Zwraca wykładnik największej potęgi dwójki mniejszej lub równej a.
 */
int floor_log2(ull a) {
  assert(a != 0);
  return numeric_limits<ull>::digits - countl_zero(a) - 1;
}

/*
 * Zwraca wykładnik najmniejszej potęgi dwójki większej lub równej a.
 */
int ceil_log2(ull a) {
  assert(a != 0);
  return numeric_limits<ull>::digits - countl_zero(a - 1);
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
 * Iteratywne potęgowanie w O(log b)
 */
ll pow(ll a, ll b) {
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
ull next_perm(ull a) {
  // Formuła zapożyczona z https://graphics.stanford.edu/~seander/bithacks.html
  ull t = a | (a - 1);
  return (t + 1) | (((~t & -~t) - 1) >> (countr_zero(a) + 1));
}
