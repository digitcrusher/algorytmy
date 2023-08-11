/*
 * Sumy prefiksowe 2D - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <numeric>
#include <vector>

/*
 * Sumy prefiksowe 2D -
 *   Struktura danych wspierająca operację obliczenia sum z góry na dół sum
 *   wierszy od lewej do prawej danej podmacierzy elementów (get) w O(1).
 *
 * Add: (Value, Value) -> Value
 *   Łączy dwie sąsiednie podmacierze elementów.
 * Sub: (Value, Value) -> Value
 *   Operacja odwrotna do Add
 *
 * Add i Sub muszą spełniać poniższe własności:
 * - Add(Sub(a, a), b) = b
 * - Sub(Add(a, b), c) = Add(Sub(a, c), b)
 * oraz co najmniej jeden z poniższych dwóch zestawów:
 * - Add(a, b) = Add(b, a) - Add jest przemienne.
 * - Add(Add(a, b), c) = Add(a, Add(b, c)) - Add jest łączne.
 * lub:
 * - Sub(a, Add(b, a)) = Sub(Sub(a, a), b)
 * - Sub(Add(a, b), c) = Add(a, Sub(b, c))
 */
template<class Value, class Add, class Sub>
struct PrefixSums2D {
  Add add;
  Sub sub;

  vector<vector<Value>> sums;

  PrefixSums2D(vector<vector<Value>> const& elems, Add add = Add(), Sub sub = Sub()):
    sums(elems), add(add), sub(sub)
  {
    partial_sum(sums[0].begin(), sums[0].end(), sums[0].begin(), add);
    for(int y = 1; y < sums.size(); y++) {
      partial_sum(sums[y].begin(), sums[y].end(), sums[y].begin(), add);
      for(int x = 0; x < sums[y].size(); x++) {
        sums[y][x] = add(sums[y - 1][x], sums[y][x]);
      }
    }
  }

  Value get(int x1, int y1, int x2, int y2) {
    assert(x1 <= x2 && y1 <= y2);
    if(x1 == 0 && y1 == 0) {
      return sums[y2][x2];
    } else if(x1 == 0) {
      return sub(sums[y2][x2], sums[y1 - 1][x2]);
    } else if(y1 == 0) {
      return sub(sums[y2][x2], sums[y2][x1 - 1]);
    } else {
      return sub(add(sums[y1 - 1][x1 - 1], sub(sums[y2][x2], sums[y1 - 1][x2])), sums[y2][x1 - 1]);
    }
  }
};
