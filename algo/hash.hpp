/*
 * Haszowanie rzeczy ze standardowej biblioteki - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <tuple>
#include <utility>
#include <vector>

template<class A, class... B>
struct hash_many {
  size_t operator()(A const& a, B const&... b) const {
    auto x = hash<A>()(a), y = hash_many<B...>()(b...);
    // Formuła zapożyczona z biblioteki Boost
    return x ^ (y + 0x9e3779b9 + (x << 6) + (x >> 2));
  }
};
template<class A>
struct hash_many<A> {
  size_t operator()(A const& x) const {
    return hash<A>()(x);
  }
};

template<class A, class B>
struct std::hash<pair<A, B>> {
  size_t operator()(pair<A, B> const& pair) const {
    return std::apply(hash_many<A, B>(), pair);
  }
};

template<class... A>
struct std::hash<tuple<A...>> {
  size_t operator()(tuple<A...> const& tuple) const {
    return std::apply(hash_many<A...>(), tuple);
  }
};

template<class A>
struct std::hash<vector<A>> {
  size_t operator()(vector<A> const& vec) const {
    if(vec.empty()) {
      return 0;
    }
    auto result = hash<A>()(vec[0]);
    for(auto const& i: vec | v::drop(1)) {
      result = hash_many<size_t, A>()(result, i);
    }
    return result;
  }
};
