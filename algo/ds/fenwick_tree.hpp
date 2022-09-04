/*
 * Drzewo Fenwicka - digitcrusher/algorytmy
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
 * Drzewo Fenwicka -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego przedziału
 *   elementów (get) i modyfikacji jednego elementu (modify) w O(log n). Zużywa
 *   O(n) pamięci.
 *
 * Add: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów.
 * Sub: (Value, Value) -> Value
 *   Operacja odwrotna do Add.
 * ApplyChange: (Value, Change) -> Value
 *   Aplikuje zmianę w jednym elemencie na spójny przedział elementów.
 *
 * Add i Sub muszą spełniać poniższe własności:
 * - Add(Add(a, b), c) = Add(a, Add(b, c)) - Add jest łączne.
 * - Add(Sub(a, a), b) = b
 * - Sub(Add(a, b), c) = Add(Sub(a, c), b)
 */
template<class Value, class Add, class Sub, class Change, class ApplyChange>
struct FenwickTree {
  Add add;
  Sub sub;
  ApplyChange apply_change;

  int elemc;
  vector<Value> sums;

  FenwickTree(vector<Value> const& elems,
              Add add = Add(), Sub sub = Sub(),
              ApplyChange apply_change = ApplyChange()):
    elemc(elems.size()), sums(elems),
    add(add), sub(sub), apply_change(apply_change)
  {
    for(int i = 1; i < elemc; i++) {
      sums[i] = add(sums[i - 1], sums[i]);
    }
    for(int i = elemc - 1; i >= 0; i--) {
      if(sum_l(i) == 0) continue;
      sums[i] = sub(sums[i], sums[sum_l(i) - 1]);
    }
  }

  int sum_l(int r) {
    return r & (r + 1);
  }

  Value get(int l, int r) {
    assert(l <= r);
    if(l != 0) {
      return sub(get(0, r), get(0, l - 1));
    } else {
      Value result = sums[r];
      r = sum_l(r) - 1;
      while(r >= 0) {
        result = add(sums[r], result);
        r = sum_l(r) - 1;
      }
      return result;
    }
  }
  void modify(int idx, Change change) {
    assert(idx < elemc);
    while(idx < elemc) {
      sums[idx] = apply_change(sums[idx], change);
      idx |= idx + 1;
    }
  }
};
