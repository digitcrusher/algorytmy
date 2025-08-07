/*
 * Drzewo Fenwicka przedział-punkt - digitcrusher/algorytmy
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
 * Drzewo Fenwicka przedział-punkt -
 *   Struktura danych wspierająca operacje obliczenia wartości jednego
 *   elementu (get) i modyfikacji przedziału elementów (modify) w O(log n).
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
struct FenwickTreeRangePoint {
  ApplyChange apply_change;
  MergeChange merge_change;
  NegateChange negate_change;

  int elemc;
  vector<Value> values;
  vector<Change> changes;

  FenwickTreeRangePoint(vector<Value> const& elems, Change neutral_change,
                        ApplyChange apply_change = {},
                        MergeChange merge_change = {},
                        NegateChange negate_change = {}):
    elemc(elems.size()), values(elems), changes(elemc, neutral_change),
    apply_change(apply_change), merge_change(merge_change), negate_change(negate_change) {}

  FenwickTreeRangePoint(int elemc, Value zero, Change neutral_change,
                        ApplyChange apply_change = {},
                        MergeChange merge_change = {},
                        NegateChange negate_change = {}):
    elemc(elemc), values(elemc, zero), changes(elemc, neutral_change),
    apply_change(apply_change), merge_change(merge_change), negate_change(negate_change) {}

  int sum_l(int r) {
    return r & (r + 1);
  }

  Value get(int idx) {
    Value result = values[idx];
    while(idx < elemc) {
      result = apply_change(result, changes[idx]);
      idx |= idx + 1;
    }
    return result;
  }
  void modify(int l, int r, Change change) {
    assert(0 <= l && l <= r);
    if(l != 0) {
      modify(0, r, change);
      modify(0, l - 1, negate_change(change));
    } else {
      while(r >= 0) {
        changes[r] = merge_change(changes[r], change);
        r = sum_l(r) - 1;
      }
    }
  }
};
