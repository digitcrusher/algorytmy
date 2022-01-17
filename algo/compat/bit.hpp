/*
 * Kompatybilnościowa implementacja <bit> z C++17 - digitcrusher/algorytmy
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

#if __cplusplus < 201402L
# include <limits>
# if defined(__GLIBCXX__) || defined(__GLIBCPP__)
namespace std {
  template<class T>
  int countl_zero(T a) {
    // Wyjaśnienie tego ifa znajduje się w tests/compat/bit.cpp
    int digit_diff = numeric_limits<ull>::digits - numeric_limits<T>::digits;
    return a == 0 ? numeric_limits<T>::digits : __builtin_clzll(a) - digit_diff;
  }
}
# else
namespace std {
  template<class T>
  int countl_zero(T a) {
    return numeric_limits<T>::digits - ceil(log2(a));
  }
}
# endif

#elif __cplusplus < 202002L
# include <bit>
namespace std {
  template<class T>
  int countl_zero(T a) {
    return std::__countl_zero(a);
  }
}

#else
# include <bit>
#endif
