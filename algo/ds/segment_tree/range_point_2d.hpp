/*
 * Drzewo przedziałowe przedział-punkt 2D - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
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
 * Drzewo przedziałowe przedział-punkt 2D -
 *   Struktura danych wspierająca operacje obliczenia wartości jednego elementu
 *   (get) i modyfikacji podmacierzy elementów (modify) w O(log w * log h).
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
struct SegmentTreeRangePoint2D {
  ApplyChange apply_change;
  MergeChange merge_change;

  int w, h;
  vector<vector<Value>> values;
  vector<vector<Change>> changes;

  int x_height, x_nodec;
  int y_height, y_nodec;
  int x_base_offset;
  int y_base_offset;

  SegmentTreeRangePoint2D(vector<vector<Value>> const& elems, Change neutral_change,
                          ApplyChange apply_change = ApplyChange(),
                          MergeChange merge_change = MergeChange()):
    w(elems[0].size()), h(elems.size()), values(elems),
    apply_change(apply_change), merge_change(merge_change)
  {
    x_height = ceil_log2(w) + 1;
    y_height = ceil_log2(h) + 1;
    x_nodec = (1u << x_height) - 1;
    y_nodec = (1u << y_height) - 1;
    x_base_offset = (1u << (x_height - 1)) - 1;
    y_base_offset = (1u << (y_height - 1)) - 1;
    changes.resize(y_nodec, vector(x_nodec, neutral_change));
  }

  Value get(int x, int y) {
    auto result = values[y][x];
    x += x_base_offset + 1;
    y += y_base_offset + 1;
    while(y >= 1) {
      for(int i = x; i >= 1; i /= 2) {
        result = apply_change(result, changes[y - 1][i - 1]);
      }
      y /= 2;
    }
    return result;
  }

  void modify(int x1, int y1, int x2, int y2, Change change) {
    assert(0 <= x1 && x1 <= x2 && x2 < w);
    assert(0 <= y1 && y1 <= y2 && y2 < h);

    auto modify_x = [&](int y, int x1, int x2) {
      x1 += x_base_offset + 1;
      x2 += x_base_offset + 1;
      while(x1 <= x2) {
        if(x1 % 2 != 0) {
          changes[y - 1][x1 - 1] = merge_change(changes[y - 1][x1 - 1], change);
          x1++;
        }
        if(x2 % 2 == 0) {
          changes[y - 1][x2 - 1] = merge_change(changes[y - 1][x2 - 1], change);
          x2--;
        }
        x1 /= 2, x2 /= 2;
      }
    };

    y1 += y_base_offset + 1;
    y2 += y_base_offset + 1;
    while(y1 <= y2) {
      if(y1 % 2 != 0) {
        modify_x(y1, x1, x2);
        y1++;
      }
      if(y2 % 2 == 0) {
        modify_x(y2, x1, x2);
        y2--;
      }
      y1 /= 2, y2 /= 2;
    }
  }
};
