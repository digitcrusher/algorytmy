/*
 * Sumy prefiksowe 2D - digitcrusher/algorytmy
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
#include <vector>

/*
 * Sumy prefiksowe 2D -
 *   Struktura danych wspierająca operację obliczenia sum z góry na dół sum
 *   wierszy od lewej do prawej danej podmacierzy elementów (get) w O(1). Zużywa
 *   O(w * h) pamięci.
 *
 * Add: (Value, Value) -> Value
 *   Łączy dwie sąsiednie podmacierze elementów.
 * Sub: (Value, Value) -> Value
 *   Operacja odwrotna do Add.
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

  vector<vector<Value>> pref_sum;

  PrefixSums2D(vector<vector<Value>> const& elems, Add add = Add(), Sub sub = Sub()):
    pref_sum(elems), add(add), sub(sub)
  {
    for(int x = 1; x < elems[0].size(); x++) {
      pref_sum[0][x] = add(pref_sum[0][x - 1], pref_sum[0][x]);
    }
    for(int y = 1; y < elems.size(); y++) {
      Value row = pref_sum[y][0];
      pref_sum[y][0] = add(pref_sum[y - 1][0], row);
      for(int x = 1; x < elems[y].size(); x++) {
        row = add(row, pref_sum[y][x]);
        pref_sum[y][x] = add(pref_sum[y - 1][x], row);
      }
    }
  }

  Value get(int x1, int y1, int x2, int y2) {
    assert(x1 <= x2 && y1 <= y2);
    if(x1 == 0 && y1 == 0) {
      return pref_sum[y2][x2];
    } else if(x1 == 0) {
      return sub(pref_sum[y2][x2], pref_sum[y1 - 1][x2]);
    } else if(y1 == 0) {
      return sub(pref_sum[y2][x2], pref_sum[y2][x1 - 1]);
    } else {
      return sub(add(pref_sum[y1 - 1][x1 - 1], sub(pref_sum[y2][x2], pref_sum[y1 - 1][x2])), pref_sum[y2][x1 - 1]);
    }
  }
};
