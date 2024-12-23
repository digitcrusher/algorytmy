/*
 * Wyszukiwanie wzorca w tekście - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/mod.hpp"
#include "string/prefix_func.hpp"
#include "string/rolling_hash.hpp"

/*
 * Algorytm Rabina-Karpa -
 *   Znajduje pozycje wszystkich wystąpień wzorca
 *   w ciągu za pomocą haszowania w O(n * m).
 */
template<int alpha_size>
vector<int> search_rabin_karp(string const& str, string const& pattern, auto alpha_to_num) {
  int n = str.size(), m = pattern.size();

  using Z = Z<(1ull << 62) - 57, true>;
  Z pattern_hash = 0;
  for(auto i: pattern) {
    pattern_hash = pattern_hash * (alpha_size + 1) + alpha_to_num(i) + 1;
  }

  vector<int> result;

  RollingHash<Z, alpha_size, decltype(alpha_to_num)> window(alpha_to_num);
  for(auto i: v::iota(0, n)) {
    window.push(str[i]);
    if(window.size() > pattern.size()) {
      window.pop();
    }
    if(window.size() == pattern.size() && window.hash == pattern_hash) {
      auto start = i - m + 1;
      if(r::all_of(v::iota(0, m), λ(str[start + _] == pattern[_]))) {
        result.push_back(start);
      }
    }
  }

  return result;
}

/*
 * Algorytm Knutha-Morrisa-Pratta -
 *   Znajduje pozycje wszystkich wystąpień wzorca w O(n + m).
 */
vector<int> search_kmp(string const& str, string const& pattern) {
  int n = str.size(), m = pattern.size();

  vector<int> result;

  auto kmp = prefix_func(pattern);
  auto matchedc = 0;
  for(auto i: v::iota(0, n)) {
    while(matchedc > 0 && str[i] != pattern[matchedc]) {
      matchedc = kmp[matchedc];
    }
    if(str[i] == pattern[matchedc]) {
      matchedc++;
      if(matchedc == m) {
        matchedc = kmp[matchedc];
        result.push_back(i - m + 1);
      }
    }
  }

  return result;
}
