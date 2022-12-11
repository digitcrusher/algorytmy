/*
 * Tablica sufiksowa - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "string/prefix_hashes.hpp"
#include <algorithm>
#include <string>
#include <vector>

/*
 * Oblicza tablicę sufiksową, czyli tablicę początków posortowanych
 * leksykograficznie sufiksów, przy użyciu haszowania w O(n log^2 n).
 */
template<int alpha_size, class AlphaToNum>
vector<int> suffix_array(string const& str, AlphaToNum alpha_to_num = AlphaToNum()) {
  int const n = str.size();

  vector<int> result(n);
  for(int i = 0; i < n; i++) {
    result[i] = i;
  }

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
    if(left == max_common_prefix) {
      return a > b;
    } else {
      return str[a + left] < str[b + left];
    }
  });

  return result;
}
