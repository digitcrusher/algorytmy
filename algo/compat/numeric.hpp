/*
 * Kompatybilnościowa implementacja <numeric> z C++17 - digitcrusher/algorytmy
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
#include <cmath>

// TODO: https://stackoverflow.com/questions/68772236/what-is-the-difference-between-std-gcd-and-stdgcd

#if __cplusplus < 201402L
# if defined(__GLIBCXX__) || defined(__GLIBCPP__)
#   include <iterator>
#   include <bits/stl_algo.h>
namespace std {
  ll gcd(ll a, ll b) {
    return std::__gcd(abs(a), abs(b));
  }
}
# else
namespace std {
  ll gcd(ll a, ll b) {
    if(b == 0) {
      return abs(a);
    }
    return gcd(b, a % b);
  }
}
# endif

namespace std {
  ll lcm(ll a, ll b) {
    assert(a != 0);
    assert(b != 0);
    return abs(a) / gcd(a, b) * abs(b);
  }
}

#elif __cplusplus < 201703L
# include <experimental/numeric>
namespace std {
  using experimental::gcd;
  using experimental::lcm;
}

#else
# include <numeric>
#endif
