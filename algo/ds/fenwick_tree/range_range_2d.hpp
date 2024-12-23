/*
 * Drzewo Fenwicka przedział-przedział 2D - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "ds/fenwick_tree/point_range_2d.hpp"

/*
 * Drzewo Fenwicka przedział-przedział 2D -
 *   Struktura danych wspierająca operacje obliczenia sumy podmacierzy
 *   elementów (get) i modyfikacji (modify) w O(log w * log h).
 *
 * Add: (Value, Value) -> Value
 *   Łaczy dwie sumy elementów.
 * Sub: (Value, Value) -> Value
 *   Operacja odwrotna do Add
 * ApplyChange: (Value, Change, int) -> Value
 *   Wielokrotnie aplikuje zmianę jednego elementu na sumę elementów.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 * NegateChange: Change -> Change
 *   Zwraca element odwrotny dla ApplyChange.
 * MultiplyChange: (Change, int) -> Change
 *   Wielokrotnie kumuluje zmianę ze sobą.
 *
 * Powyższe operacje muszą spełniać poniższe własności:
 * - Add(Add(a, b), c) = Add(a, Add(b, c)) - Add jest łączne.
 * - Add(a, b) = Add(b, a) - Add jest przemienne.
 * - Add(Sub(a, a), b) = b
 * - Sub(Add(a, b), c) = Add(Sub(a, c), b)
 * - ApplyChange(Add(x, y), a, n) = Add(ApplyChange(x, a, n), y)
 * - (i, j > 0 & i + j = n) => ApplyChange(Add(x, y), a, n) = Add(ApplyChange(x, a, i), ApplyChange(y, a, j))
 * - ApplyChange(x, MergeChange(a, b), n) = ApplyChange(ApplyChange(x, a, n), b, n)
 * - ApplyChange(ApplyChange(a, b, n), NegateChange(b), n) = a
 * - ApplyChange(a, MultiplyChange(b, n), m) = ApplyChange(a, b, n * m)
 * - ApplyChange(a, neutral_change, n) = a - neutral_change jest elementem neutralnym dla ApplyChange.
 */
template<
  class Value,
  class Add,
  class Sub,
  class Change,
  class ApplyChange,
  class MergeChange,
  class NegateChange,
  class MultiplyChange
> struct FenwickTreeRangeRange2D {
  Add add;
  Sub sub;
  ApplyChange apply_change;
  NegateChange negate_change;
  MultiplyChange multiply_change;

  struct ValuesApplyChange {
    ApplyChange apply_change;

    ValuesApplyChange(ApplyChange apply_change): apply_change(apply_change) {}

    Value operator()(Value value, pair<Change, int> change) {
      return apply_change(value, change.first, change.second);
    }
  };

  int w, h;
  FenwickTree2D<Value, Add, Sub, pair<Change, int>, ValuesApplyChange> values;
  FenwickTree2D<Change, MergeChange, MergeChange, Change, MergeChange> changes_x, changes_y, changes_xy;

  FenwickTreeRangeRange2D(vector<vector<Value>> const& elems, Change neutral_change,
                          Add add = {}, Sub sub = {},
                          ApplyChange apply_change = {},
                          MergeChange merge_change = {},
                          NegateChange negate_change = {},
                          MultiplyChange multiply_change = {}):
    w(elems[0].size()), h(elems.size()),
    values(elems, add, sub, ValuesApplyChange(apply_change)),
    changes_x(w, h, neutral_change, merge_change, merge_change, merge_change),
    changes_y(w, h, neutral_change, merge_change, merge_change, merge_change),
    changes_xy(w, h, neutral_change, merge_change, merge_change, merge_change),
    add(add), sub(sub), apply_change(apply_change), negate_change(negate_change), multiply_change(multiply_change) {}

  FenwickTreeRangeRange2D(int w, int h, Value zero, Change neutral_change,
                          Add add = {}, Sub sub = {},
                          ApplyChange apply_change = {},
                          MergeChange merge_change = {},
                          NegateChange negate_change = {},
                          MultiplyChange multiply_change = {}):
    w(w), h(h),
    values(w, h, zero, add, sub, ValuesApplyChange(apply_change)),
    changes_x(w, h, neutral_change, merge_change, merge_change, merge_change),
    changes_y(w, h, neutral_change, merge_change, merge_change, merge_change),
    changes_xy(w, h, neutral_change, merge_change, merge_change, merge_change),
    add(add), sub(sub), apply_change(apply_change), negate_change(negate_change), multiply_change(multiply_change) {}

  Value get(int x1, int y1, int x2, int y2) {
    assert(x1 >= 0 && y1 >= 0);
    assert(x1 <= x2 && y1 <= y2);
    if(x1 != 0 && y1 != 0) {
      return sub(add(get(0, 0, x1 - 1, y1 - 1), sub(get(0, 0, x2, y2), get(0, 0, x2, y1 - 1))), get(0, 0, x1 - 1, y2));
    } else if(x1 != 0) {
      return sub(get(0, 0, x2, y2), get(0, 0, x1 - 1, y2));
    } else if(y1 != 0) {
      return sub(get(0, 0, x2, y2), get(0, 0, x2, y1 - 1));
    } else {
      Value result = values.get(0, 0, x2, y2);
      if(x2 != w - 1) {
        result = apply_change(result, changes_x.get(0, 0, w - 1 - (x2 + 1), y2), x2 + 1);
      }
      if(y2 != h - 1) {
        result = apply_change(result, changes_y.get(0, 0, x2, h - 1 - (y2 + 1)), y2 + 1);
      }
      if(x2 != w - 1 && y2 != h - 1) {
        result = apply_change(result, changes_xy.get(0, 0, w - 1 - (x2 + 1), h - 1 - (y2 + 1)), (x2 + 1) * (y2 + 1));
      }
      return result;
    }
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
      values.modify(x2, y2, {change, (x2 + 1) * (y2 + 1)});
      changes_x.modify(w - 1 - x2, y2, multiply_change(change, y2 + 1));
      changes_y.modify(x2, h - 1 - y2, multiply_change(change, x2 + 1));
      changes_xy.modify(w - 1 - x2, h - 1 - y2, change);
    }
  }
};
