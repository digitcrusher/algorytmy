/*
 * Sparse table - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/int.hpp"
#include <vector>

/*
 * Sparse table -
 *   Struktura danych wspierająca operację obliczenia sumy spójnego przedziału
 *   elementów (get) w O(1) po wstępnym przetwarzaniu w O(n log n). Zużywa
 *   O(n log n) pamięci. Ta implementacja zakłada, że początkowa tablica nigdy
 *   nie jest pusta.
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
  vector<vector<Value>> segs;

  SparseTable(vector<Value> const& elems, Sum sum = Sum()):
    elemc(elems.size()), sum(sum)
  {
    height = elemc == 1 ? 1 : ceil_log2(elemc);

    segs.resize(height, vector<Value>(elemc));
    for(int i = 0; i < elemc; i++) {
      segs[0][i] = elems[i];
    }
    for(int j = 1; j < height; j++) {
      for(int i = 0; i < elemc; i++) {
        segs[j][i] = sum(
          segs[j - 1][i],
          segs[j - 1][min(i + level_elemc(j - 1), elemc - 1)]
        );
      }
    }
  }

  int level_elemc(int level) {
    return 1u << level;
  }

  Value get(int l, int r) {
    assert(l <= r && r < elemc);
    if(l == r) {
      return segs[0][l];
    }
    int level = ceil_log2(r - l + 1) - 1;
    return sum(segs[level][l], segs[level][r - level_elemc(level) + 1]);
  }
};
