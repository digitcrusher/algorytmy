/*
 * Drzewo Fenwicka przedział-przedział - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "ds/fenwick_tree/point_range.hpp"

/*
 * Drzewo Fenwicka przedział-przedział -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego
 *   przedziału elementów (get) i modyfikacji (modify) w O(log n).
 *
 * Add: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów.
 * Sub: (Value, Value) -> Value
 *   Operacja odwrotna do Add
 * ApplyChange: (Value, Change, int) -> Value
 *   Wielokrotnie aplikuje zmianę jednego elementu na spójny przedział elementów.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 * NegateChange: Change -> Change
 *   Zwraca element odwrotny dla ApplyChange.
 *
 * Powyższe operacje muszą spełniać poniższe własności:
 * - Add(Add(a, b), c) = Add(a, Add(b, c)) - Add jest łączne.
 * - Add(Sub(a, a), b) = b
 * - Sub(Add(a, b), c) = Add(Sub(a, c), b)
 * - ApplyChange(Add(x, y), a, n) = Add(ApplyChange(x, a, n), y) = Add(x, ApplyChange(y, a, n))
 * - (i, j > 0 & i + j = n) => ApplyChange(Add(x, y), a, n) = Add(ApplyChange(x, a, i), ApplyChange(y, a, j))
 * - ApplyChange(x, MergeChange(a, b), n) = ApplyChange(ApplyChange(x, a, n), b, n)
 * - ApplyChange(ApplyChange(a, b, n), NegateChange(b), n) = a
 * - ApplyChange(a, neutral_change, n) = a - neutral_change jest elementem neutralnym dla ApplyChange.
 */
template<
  class Value,
  class Add,
  class Sub,
  class Change,
  class ApplyChange,
  class MergeChange,
  class NegateChange
> struct FenwickTreeRangeRange {
  Sub sub;
  ApplyChange apply_change;
  NegateChange negate_change;

  struct ValuesApplyChange {
    ApplyChange apply_change;

    ValuesApplyChange(ApplyChange apply_change): apply_change(apply_change) {}

    Value operator()(Value value, pair<Change, int> change) {
      return apply_change(value, change.first, change.second);
    }
  };

  int elemc;
  FenwickTree<Value, Add, Sub, pair<Change, int>, ValuesApplyChange> values;
  FenwickTree<Change, MergeChange, MergeChange, Change, MergeChange> changes;

  FenwickTreeRangeRange(vector<Value> const& elems, Change neutral_change,
                        Add add = {}, Sub sub = {},
                        ApplyChange apply_change = {},
                        MergeChange merge_change = {},
                        NegateChange negate_change = {}):
    elemc(elems.size()), values(elems, add, sub, ValuesApplyChange(apply_change)),
    changes(elemc, neutral_change, merge_change, merge_change, merge_change),
    sub(sub), apply_change(apply_change), negate_change(negate_change) {}

  FenwickTreeRangeRange(int elemc, Value zero, Change neutral_change,
                        Add add = {}, Sub sub = {},
                        ApplyChange apply_change = {},
                        MergeChange merge_change = {},
                        NegateChange negate_change = {}):
    elemc(elemc), values(elemc, zero, add, sub, ValuesApplyChange(apply_change)),
    changes(elemc, neutral_change, merge_change, merge_change, merge_change),
    sub(sub), apply_change(apply_change), negate_change(negate_change) {}

  Value get(int l, int r) {
    assert(0 <= l && l <= r);
    if(l != 0) {
      return sub(get(0, r), get(0, l - 1));
    } else if(r == elemc - 1) {
      return values.get(0, r);
    } else {
      return apply_change(values.get(0, r), changes.get(0, elemc - 1 - (r + 1)), r + 1);
    }
  }

  void modify(int l, int r, Change change) {
    assert(0 <= l && l <= r);
    if(l != 0) {
      modify(0, r, change);
      modify(0, l - 1, negate_change(change));
    } else {
      values.modify(r, {change, r + 1});
      changes.modify(elemc - 1 - r, change);
    }
  }
};
