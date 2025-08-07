/*
 * Sparse table - digitcrusher/algorytmy
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
 * Sparse table -
 *   Struktura danych wspierająca operację obliczenia sumy spójnego przedziału
 *   elementów (get) w O(1) po wstępnym przetwarzaniu w O(n log n). Zużywa
 *   O(n log n) pamięci.
 *
 * Sum: (Value, Value) -> Value
 *   Łączy dwa nachodzące na siebie lub nie przedziały elementów. Sum musi być
 *   łączne, przemienne i idempotentne, czyli:
 *   - Sum(Sum(a, b), c) = Sum(a, Sum(b, c))
 *   - Sum(a, b) = Sum(b, a)
 *   - Sum(a, a) = a
 */
template<class Value, class Sum>
struct SparseTable {
  Sum sum;

  int elemc, height;
  vector<vector<Value>> sums;

  SparseTable(vector<Value> const& elems, Sum sum = {}):
    elemc(elems.size()), sum(sum)
  {
    height = elemc == 1 ? 1 : bit_width(elemc - 1u);

    sums.resize(height, vector<Value>(elemc));
    sums[0] = elems;
    for(auto j: v::iota(1, height)) {
      for(auto i: v::iota(0, elemc)) {
        sums[j][i] = sum(
          sums[j - 1][i],
          sums[j - 1][min(i + level_elemc(j - 1), elemc - 1)]
        );
      }
    }
  }

  int level_elemc(int level) const {
    return 1u << level;
  }

  Value get(int l, int r) const {
    assert(l <= r && r < elemc);
    if(l == r) {
      return sums[0][l];
    }
    auto level = bit_width<uint>(r - l) - 1;
    return sum(sums[level][l], sums[level][r - level_elemc(level) + 1]);
  }
};
