/*
 * Drzewo przedziałowe przedział-punkt - digitcrusher/algorytmy
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
 * Drzewo przedziałowe przedział-punkt -
 *   Struktura danych wspierająca operacje obliczenia wartości jednego elementu
 *   (get) i modyfikacji przedziału elementów (modify) w O(log n). Zużywa O(n)
 *   pamięci. Ta implementacja zakłada, że początkowa tablica nigdy nie
 *   jest pusta.
 *
 * ApplyChange: (Value, Change) -> Value
 *   Aplikuje zmianę na jeden element.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 *
 * Powyższe operacje muszą spełniać poniższe własności:
 * - ApplyChange(ApplyChange(a, b), c) = ApplyChange(ApplyChange(a, c), b) - ApplyChange jest przemienne.
 * - ApplyChange(a, MergeChange(b, c)) = ApplyChange(ApplyChange(a, b), c)
 * - ApplyChange(a, neutral_change) = a - neutral_change jest elementem neutralnym dla ApplyChange.
 */
template<class Value, class Change, class ApplyChange, class MergeChange>
struct SegmentTreeRangePoint {
  ApplyChange apply_change;
  MergeChange merge_change;

  int elemc;
  vector<Value> values;
  vector<Change> changes;

  int height, nodec;
  int base_offset;

  SegmentTreeRangePoint(vector<Value> const& elems, Change neutral_change,
                        ApplyChange apply_change = ApplyChange(),
                        MergeChange merge_change = MergeChange()):
    elemc(elems.size()), values(elems), apply_change(apply_change), merge_change(merge_change)
  {
    height = ceil_log2(elemc) + 1;
    nodec = (1u << height) - 1;
    base_offset = (1u << (height - 1)) - 1;
    changes.resize(nodec / 2, neutral_change);
  }

  Value get(int idx) {
    Value result = values[idx];
    idx = (base_offset + idx + 1) / 2;
    while(idx >= 1) {
      result = apply_change(result, changes[idx - 1]);
      idx /= 2;
    }
    return result;
  }

  void modify(int l, int r, Change change) {
    assert(0 <= l && l <= r && r < elemc);
    auto touch = [&](int num) {
      if(num - 1 < base_offset) {
        changes[num - 1] = merge_change(changes[num - 1], change);
      } else {
        values[num - base_offset - 1] = apply_change(values[num - base_offset - 1], change);
      }
    };
    l += base_offset + 1;
    r += base_offset + 1;
    while(l <= r) {
      if(l % 2 == 1) {
        touch(l);
        l++;
      }
      if(r % 2 == 0) {
        touch(r);
        r--;
      }
      l /= 2, r /= 2;
    }
  }
};
