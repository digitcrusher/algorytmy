/*
 * Drzewo przedziałowe punkt-przedział - digitcrusher/algorytmy
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
#include "math/int.hpp"
#include <vector>

/*
 * Iteratywne drzewo przedziałowe punkt-przedział -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego przedziału
 *   elementów (get) i ustawienia elementu (set) w O(log n). Zużywa O(n)
 *   pamięci. Ta implementacja zakłada, że początkowa tablica nigdy nie
 *   jest pusta, oraz sumuje domyślnie zainicjalizowane wartości.
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów. Sum musi być łączne, czyli
 *   Sum(Sum(a, b), c) = Sum(a, Sum(b, c)).
 */
template<class Value, class Sum>
struct SegmentTree {
  Sum sum;

  int elemc;
  vector<Value> nodes;

  int height, nodec;
  int base_offset;

  SegmentTree(vector<Value> const& elems, Sum sum = Sum()):
    elemc(elems.size()), sum(sum)
  {
    height = ceil_log2(elemc + 2) + 1;
    nodec = (1u << height) - 1;
    base_offset = 1u << (height - 1);
    nodes.resize(nodec);

    for(int i = 0; i < elemc; i++) {
      nodes[base_offset + i] = elems[i];
    }
    resum();
  }

  Value get(int l, int r) {
    assert(l <= r && r < elemc);
    Value left{}, right{};
    l += base_offset;
    r += base_offset + 2;
    while(l / 2 != r / 2) {
      if(l % 2 != 1) {
        left = sum(left, nodes[l]);
      }
      if(r % 2 != 0) {
        right = sum(nodes[r - 2], right);
      }
      l /= 2, r /= 2;
    }
    return sum(left, right);
  }

  void set(int idx, Value val) {
    assert(0 <= idx && idx < elemc);
    nodes[base_offset + idx] = val;
    idx = (base_offset + idx + 1) / 2;
    while(idx >= 1) {
      nodes[idx - 1] = sum(nodes[2 * idx - 1], nodes[2 * idx]);
      idx /= 2;
    }
  }

  void resum(int num = 1) {
    if(num <= base_offset - 1) {
      resum(2 * num);
      resum(2 * num + 1);
      nodes[num - 1] = sum(nodes[2 * num - 1], nodes[2 * num]);
    }
  }
};
