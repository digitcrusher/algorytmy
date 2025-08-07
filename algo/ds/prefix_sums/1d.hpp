/*
 * Sumy prefiksowe - digitcrusher/algorytmy
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
 * Sumy prefiksowe -
 *   Struktura danych wspierająca operację obliczenia sumy spójnego
 *   przedziału elementów od lewej od prawej (get) w O(1).
 *
 * Add: (Value, Value) -> Value
 *   Łączy dwa sąsiednie przedziały elementów.
 * Sub: (Value, Value) -> Value
 *   Operacja odwrotna do Add
 *
 * Add i Sub muszą spełniać poniższe własności:
 * - Add(Sub(a, a), b) = b
 * - Sub(Add(a, b), c) = Add(Sub(a, c), b)
 */
template<class Value, class Add, class Sub>
struct PrefixSums {
  Add add;
  Sub sub;

  vector<Value> sums;

  PrefixSums(vector<Value> const& elems, Add add = {}, Sub sub = {}):
    sums(elems), add(add), sub(sub)
  {
    partial_sum(sums.begin(), sums.end(), sums.begin(), add);
  }

  Value get(int l, int r) const {
    assert(l <= r);
    if(l == 0) {
      return sums[r];
    } else {
      return sub(sums[r], sums[l - 1]);
    }
  }
};
