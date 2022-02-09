/*
 * Sumy prefiksowe - digitcrusher/algorytmy
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
 * Sumy prefiksowe -
 *   Struktura danych wspierająca operację obliczenia sumy spójnego przedziału
 *   elementów od lewej od prawej (get) w O(1). Zużywa O(n) pamięci.
 *
 * Add: (Value, Value) -> Value
 *   Łączy dwa sąsiednie przedziały elementów.
 * Sub: (Value, Value) -> Value
 *   Operacja odwrotna do Add.
 *
 * Add i Sub muszą spełniać poniższe własności:
 * - Add(Sub(a, a), b) = b
 * - Sub(Add(a, b), c) = Add(Sub(a, c), b)
 */
template<class Value, class Add, class Sub>
struct PrefixSums {
  Add add;
  Sub sub;

  vector<Value> pref_sum;

  PrefixSums(vector<Value> const& elems, Add add = Add(), Sub sub = Sub()):
    pref_sum(elems), add(add), sub(sub)
  {
    for(int i = 1; i < elems.size(); i++) {
      pref_sum[i] = add(pref_sum[i - 1], pref_sum[i]);
    }
  }

  Value get(int l, int r) {
    assert(l <= r);
    if(l == 0) {
      return pref_sum[r];
    } else {
      return sub(pref_sum[r], pref_sum[l - 1]);
    }
  }
};
