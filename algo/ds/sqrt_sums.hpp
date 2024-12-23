/*
 * Sumy pierwiastkowe - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <cmath>

/*
 * Sumy pierwiastkowe -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego przedziału
 *   elementów (get) w O(sqrt(n)) i modyfikacji jednego elementu (modify) w O(1)
 *   zwykle używana do przyśpieszania algorytmu Mo.
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów.
 * ApplyChange: (Value, Change) -> Value
 *   Aplikuje zmianę w jednym elemencie na spójny przedział elementów.
 *
 * Powyższe operacje muszą spełniać poniższe własności:
 * - Sum(Sum(a, b), c) = Sum(a, Sum(b, c)) - Sum jest łączne.
 * - ApplyChange(Sum(x, y), a) = Sum(ApplyChange(x, a), y) = Sum(x, ApplyChange(y, a))
 */
template<class Value, class Sum, class Change, class ApplyChange>
struct SqrtSums {
  Sum sum;
  ApplyChange apply_change;

  int elemc, block_size;
  vector<Value> elems, sums;

  SqrtSums(vector<Value> const& elems, Sum sum = {},
           ApplyChange apply_change = {}):
    elemc(elems.size()), block_size(max<int>(sqrt(elemc), 1)),
    elems(elems), sums(elemc / block_size),
    sum(sum), apply_change(apply_change)
  {
    for(auto i: v::iota(0, (int) sums.size())) {
      sums[i] = elems[i * block_size];
      for(auto j: v::iota(1, min(block_size, elemc - i * block_size))) {
        sums[i] = sum(sums[i], elems[i * block_size + j]);
      }
    }
  }

  SqrtSums(int elemc, Value zero, Sum sum = {},
           ApplyChange apply_change = {}):
    elemc(elemc), block_size(max<int>(sqrt(elemc), 1)),
    elems(elemc, zero), sums(elemc / block_size, zero),
    sum(sum), apply_change(apply_change) {}

  Value get(int l, int r) {
    assert(l <= r && r < elemc);
    Value result = elems[l];
    for(auto i = l + 1; i <= r;) {
      if(i % block_size == 0 && i + block_size - 1 <= r) {
        result = sum(result, sums[i / block_size]);
        i += block_size;
      } else {
        result = sum(result, elems[i]);
        i++;
      }
    }
    return result;
  }

  void modify(int idx, Change change) {
    elems[idx] = apply_change(elems[idx], change);
    sums[idx / block_size] = apply_change(sums[idx / block_size], change);
  }
};
