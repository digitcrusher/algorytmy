/*
 * Różne operacje bitowe - digitcrusher/algorytmy
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
#if __cplusplus >= 201402L || defined(__GLIBCXX__) || defined(__GLIBCPP__)
# include <bit>
# include <limits>
#else
# include <cmath>
#endif

ull floor_log2(ull a) {
  assert(a != 0);
#if __cplusplus >= 201402L || defined(__GLIBCXX__) || defined(__GLIBCPP__)
# if __cplusplus > 201703L // TODO: Zmień to na liczbę wersji C++20, gdy zostanie wydane.
  ull clz = std::countl_zero(a);
# elif __cplusplus >= 201402L
  ull clz = std::__countl_zero(a);
# elif defined(__GLIBCXX__) || defined(__GLIBCPP__)
  ull clz = __builtin_clzll(a);
# endif
  ull log = std::numeric_limits<ull>::digits - clz - 1;
#else
  ull log = std::floor(std::log2(a));
#endif
  return log;
}



ull ceil_log2(ull a) {
  assert(a != 0);
#if __cplusplus >= 201402L || defined(__GLIBCXX__) || defined(__GLIBCPP__)
# if __cplusplus > 201703L // TODO: Tu też
  ull clz = std::countl_zero(a - 1);
# elif __cplusplus >= 201402L
  ull clz = std::__countl_zero(a - 1);
# elif defined(__GLIBCXX__) || defined(__GLIBCPP__)
  // Wyjaśnienie tego ifa znajduje się w tests/test_bit.cpp
  ull clz = a == 1 ? std::numeric_limits<ull>::digits : __builtin_clzll(a - 1);
# endif
  ull log = std::numeric_limits<ull>::digits - clz;
#else
  ull log = std::ceil(std::log2(a));
#endif
  return log;
}
