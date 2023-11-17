/*
 * Drzewo Fenwicka 2D - digitcrusher/algorytmy
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
 * Drzewo Fenwicka 2D -
 *   Struktura danych wspierająca operacje obliczenia sumy podmacierzy elementów
 *   (get) i modyfikacji jednego elementu (modify) w O(log w * log h).
 *
 * Add: (Value, Value) -> Value
 *   Łaczy dwie sumy elementów.
 * Sub: (Value, Value) -> Value
 *   Operacja odwrotna do Add
 * ApplyChange: (Value, Change) -> Value
 *   Aplikuje zmianę w jednym elemencie na sumę elementów.
 *
 * Powyższe operacje muszą spełniać poniższe własności:
 * - Add(Add(a, b), c) = Add(a, Add(b, c)) - Add jest łączne.
 * - Add(a, b) = Add(b, a) - Add jest przemienne.
 * - Add(Sub(a, a), b) = b
 * - Sub(Add(a, b), c) = Add(Sub(a, c), b)
 * - ApplyChange(Add(a, b), c) = Add(ApplyChange(a, c), b)
 */
template<class Value, class Add, class Sub, class Change, class ApplyChange>
struct FenwickTree2D {
  Add add;
  Sub sub;
  ApplyChange apply_change;

  int w, h;
  vector<vector<Value>> sums;

  FenwickTree2D(vector<vector<Value>> const& elems,
                Add add = Add(), Sub sub = Sub(),
                ApplyChange apply_change = ApplyChange()):
    w(elems[0].size()), h(elems.size()), sums(elems),
    add(add), sub(sub), apply_change(apply_change)
  {
    partial_sum(sums[0].begin(), sums[0].end(), sums[0].begin(), add);
    for(auto y: v::iota(1, h)) {
      partial_sum(sums[y].begin(), sums[y].end(), sums[y].begin(), add);
      for(auto x: v::iota(0, w)) {
        sums[y][x] = add(sums[y - 1][x], sums[y][x]);
      }
    }

    for(auto y: v::iota(0, h) | v::reverse) {
      auto j = sum_l(y);
      for(auto x: v::iota(0, w) | v::reverse) {
        auto i = sum_l(x);
        if(i != 0 && j != 0) {
          sums[y][x] = sub(add(sums[j - 1][i - 1], sub(sums[y][x], sums[j - 1][x])), sums[y][i - 1]);
        } else if(i != 0) {
          sums[y][x] = sub(sums[y][x], sums[y][i - 1]);
        } else if(j != 0) {
          sums[y][x] = sub(sums[y][x], sums[j - 1][x]);
        }
      }
    }
  }

  int sum_l(int r) {
    return r & (r + 1);
  }

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
      Value result = sums[y2][x2];
      for(auto x = sum_l(x2) - 1; x >= 0; x = sum_l(x) - 1) {
        result = add(sums[y2][x], result);
      }
      for(auto y = sum_l(y2) - 1; y >= 0; y = sum_l(y) - 1) {
        for(auto x = x2; x >= 0; x = sum_l(x) - 1) {
          result = add(sums[y][x], result);
        }
      }
      return result;
    }
  }
  void modify(int x, int y, Change change) {
    assert(x < w && y < h);
    for(auto j = y; j < h; j |= j + 1) {
      for(auto i = x; i < w; i |= i + 1) {
        sums[j][i] = apply_change(sums[j][i], change);
      }
    }
  }
};
