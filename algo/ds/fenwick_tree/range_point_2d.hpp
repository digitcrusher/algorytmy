/*
 * Drzewo Fenwicka przedział-punkt 2D - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <vector>

/*
 * Drzewo Fenwicka przedział-punkt 2D -
 *   Struktura danych wspierająca operacje obliczenia wartości jednego elementu
 *   (get) i modyfikacji podmacierzy elementów (modify) w O(log w * log h).
 *   Zużywa O(w * h) pamięci.
 *
 * ApplyChange: (Value, Change) -> Value
 *   Aplikuje zmianę na jeden element.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 * NegateChange: Change -> Change
 *   Zwraca element odwrotny dla ApplyChange.
 *
 * Powyższe operacje muszą spełniać poniższe własności:
 * - ApplyChange(ApplyChange(a, b), c) = ApplyChange(ApplyChange(a, c), b) - ApplyChange jest przemienne.
 * - ApplyChange(a, MergeChange(b, c)) = ApplyChange(ApplyChange(a, b), c)
 * - ApplyChange(ApplyChange(a, b), NegateChange(b)) = a
 * - ApplyChange(a, neutral_change) = a - neutral_change jest elementem neutralnym dla ApplyChange.
 */
template<class Value, class Change, class ApplyChange, class MergeChange, class NegateChange>
struct FenwickTreeRangePoint2D {
  ApplyChange apply_change;
  MergeChange merge_change;
  NegateChange negate_change;

  int w, h;
  vector<vector<Value>> values;
  vector<vector<Change>> changes;

  FenwickTreeRangePoint2D(vector<vector<Value>> const& elems, Change neutral_change,
                          ApplyChange apply_change = ApplyChange(),
                          MergeChange merge_change = MergeChange(),
                          NegateChange negate_change = NegateChange()):
    w(elems[0].size()), h(elems.size()), values(elems), changes(h, vector(w, neutral_change)),
    apply_change(apply_change), merge_change(merge_change), negate_change(negate_change) {}

  int sum_l(int r) {
    return r & (r + 1);
  }

  Value get(int x, int y) {
    Value result = values[y][x];
    for(int j = y; j < h; j |= j + 1) {
      for(int i = x; i < w; i |= i + 1) {
        result = apply_change(result, changes[j][i]);
      }
    }
    return result;
  }
  void modify(int x1, int y1, int x2, int y2, Change change) {
    assert(x1 >= 0 && y1 >= 0);
    assert(x1 <= x2 && y1 <= y2);
    if(x1 != 0) {
      modify(0, y1, x2, y2, change);
      modify(0, y1, x1 - 1, y2, negate_change(change));
    } else if(y1 != 0) {
      modify(x1, 0, x2, y2, change);
      modify(x1, 0, x2, y1 - 1, negate_change(change));
    } else {
      for(int y = y2; y >= 0; y = sum_l(y) - 1) {
        for(int x = x2; x >= 0; x = sum_l(x) - 1) {
          changes[y][x] = merge_change(changes[y][x], change);
        }
      }
    }
  }
};
