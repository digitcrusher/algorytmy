/*
 * Wyszukiwanie wzorca w tekście - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "string/prefix_function.hpp"
#include "string/rolling_hash.hpp"
#include <string>
#include <vector>

/*
 * Algorytm Rabina-Karpa -
 *   Znajduje pozycje wszystkich wystąpień wzorca
 *   w ciągu za pomocą haszowania w O(n * m).
 */
template<int alpha_size, class AlphaToNum>
vector<int> search_rabin_karp(string const& str, string const& pattern,
                              AlphaToNum alpha_to_num = AlphaToNum())
{
  int const n = str.size(), m = pattern.size();
  ll const mod = 4611686018427387847;

  ll pattern_hash = 0;
  for(char c: pattern) {
    pattern_hash = mod_mul(pattern_hash, alpha_size + 1, mod) + alpha_to_num(c) + 1;
    pattern_hash %= mod;
  }

  vector<int> result;

  RollingHash<alpha_size, AlphaToNum> window(mod, alpha_to_num);
  for(int i = 0; i < n; i++) {
    window.push(str[i]);
    if(window.size() > pattern.size()) {
      window.pop();
    }
    if(window.size() == pattern.size() && window.hash == pattern_hash) {
      bool is_match = true;
      int start = i - m + 1;
      for(int j = 0; j < m && is_match; j++) {
        is_match &= str[start + j] == pattern[j];
      }
      if(is_match) {
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
  int const n = str.size(), m = pattern.size();

  vector<int> result;

  auto kmp = prefix_function(pattern);
  int matchedc = 0;
  for(int i = 0; i < n; i++) {
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
