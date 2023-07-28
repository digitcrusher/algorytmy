/*
 * Tablica sufiksowa - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "string/prefix_hashes.hpp"
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

/*
 * Oblicza tablicę sufiksową, czyli tablicę początków posortowanych
 * leksykograficznie sufiksów, przy użyciu dziel i zwyciężaj w O(n log^2 n).
 */
vector<int> suffix_array(string const& str) {
  int const n = str.size();

  vector<int> result(n);
  iota(result.begin(), result.end(), 0);

  vector<int> order(n + 1);
  for(int i = 0; i < n; i++) {
    order[i] = str[i];
  }
  order[n] = -1;
  vector<pair<int, int>> keys(n);
  for(int size = 1; size < n; size *= 2) {
    for(int i = 0; i < n; i++) {
      keys[i] = {order[i], order[min(i + size, n)]};
    }
    sort(result.begin(), result.end(), [&](int a, int b) {
      return keys[a] < keys[b];
    });
    order[result[0]] = 0;
    for(int i = 1; i < n; i++) {
      order[result[i]] = keys[result[i - 1]] == keys[result[i]] ? order[result[i - 1]] : i;
    }
  }

  return result;
}

/*
 * Oblicza tablicę sufiksową, czyli tablicę początków posortowanych
 * leksykograficznie sufiksów, przy użyciu haszowania w O(n log^2 n).
 * Ten algorytm jest wolniejszy od poprzedniego.
 */
template<int alpha_size, class AlphaToNum>
vector<int> suffix_array_hash(string const& str, AlphaToNum alpha_to_num = AlphaToNum()) {
  int const n = str.size();

  vector<int> result(n);
  iota(result.begin(), result.end(), 0);

  PrefixHashes<alpha_size, AlphaToNum> hash(str, 4611686018427387847, alpha_to_num);
  sort(result.begin(), result.end(), [&](int a, int b) {
    int max_common_prefix = min(n - a, n - b);
    int left = 0, right = max_common_prefix;
    while(left < right) {
      int mid = left + (right - left + 1) / 2;
      if(hash.get(a, a + mid - 1) == hash.get(b, b + mid - 1)) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    return left == max_common_prefix ? a > b : str[a + left] < str[b + left];
  });

  return result;
}
