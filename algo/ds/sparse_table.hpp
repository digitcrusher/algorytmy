/*
 * Sparse table - digitcrusher/algorytmy
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
#include "math/int.hpp"
#include <vector>

/*
 * Sparse table -
 *   Struktura danych wspierająca operację obliczenia sumy spójnego przedziału
 *   elementów (get) w O(1) po wstępnym przetwarzaniu w O(log n).
 *   Ta implementacja zakłada, że ciąg elementów nigdy nie jest pusty.
 *
 * Sum: (Value, Value) -> Value
 *   Łączy dwa nachodzące na siebie lub nie przedziały elementów. Sum musi być
 *   łączne, przemienne i idempotentne, czyli:
 *   - sum(sum(a, b), c) = sum(a, sum(b, c))
 *   - sum(a, b) = sum(b, a)
 *   - sum(a, a) = a
 */
template<class Value, class Sum>
struct SparseTable {
  Sum sum;

  vector<vector<Value>> segs;
  int elemc, height;

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
          segs[j - 1][min(i + level_elemc(j), elemc - 1)]
        );
      }
    }
  }

  int level_elemc(int level) {
    return 1u << level;
  }

  Value get(int l, int r) {
    if(l == r) {
      return segs[0][l];
    }
    int level = ceil_log2(r - l + 1) - 1;
    return sum(segs[level][l], segs[level][r - level_elemc(level) + 1]);
  }
};
