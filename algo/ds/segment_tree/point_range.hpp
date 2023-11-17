/*
 * Drzewo przedziałowe punkt-przedział - digitcrusher/algorytmy
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
 * Drzewo przedziałowe punkt-przedział -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego
 *   przedziału elementów (get) i ustawienia elementu (set) w O(log n).
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów. Sum musi być łączne, czyli
 *   Sum(Sum(a, b), c) = Sum(a, Sum(b, c)).
 */
template<class Value, class Sum>
struct SegmentTreePointRange {
  Value zero;
  Sum sum;

  int elemc;
  vector<Value> nodes;

  int height, nodec;
  int base_offset;

  SegmentTreePointRange(vector<Value> const& elems, Value zero, Sum sum = Sum()):
    elemc(elems.size()), zero(zero), sum(sum)
  {
    height = ceil_log2(elemc) + 1;
    nodec = (1u << height) - 1;
    base_offset = (1u << (height - 1)) - 1;
    nodes.resize(nodec, zero);

    for(auto i: v::iota(0, elemc)) {
      nodes[base_offset + i] = elems[i];
    }
    resum();
  }

  Value get(int l, int r) {
    assert(0 <= l && l <= r && r < elemc);
    auto left = zero, right = zero;
    l += base_offset + 1;
    r += base_offset + 1;
    while(l <= r) {
      if(l % 2 != 0) {
        left = sum(left, nodes[l - 1]);
        l++;
      }
      if(r % 2 == 0) {
        right = sum(nodes[r - 1], right);
        r--;
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
    if(num - 1 < base_offset) {
      resum(2 * num);
      resum(2 * num + 1);
      nodes[num - 1] = sum(nodes[2 * num - 1], nodes[2 * num]);
    }
  }
};
