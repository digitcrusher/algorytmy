/*
 * Drzewo Li Chao - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/int.hpp"

/*
 * Drzewo Li Chao -
 *   Struktura danych pozwalająca na obliczenie największej albo najmniejszej
 *   wartości funkcji liniowych w danym całkowitoliczbowym punkcie (get)
 *   i dodania nowej funkcji liniowej (insert) w O(log X), gdzie X to zakres
 *   argumentów funkcji. Zużywa O(X) pamięci.
 */
struct LinFunc {
  ll a, b;

  ll operator()(ll x) {
    return a * x + b;
  }
};
struct LiChao {
  int min_x, max_x;

  vector<LinFunc> nodes;
  int height, nodec;
  int base_nodec, base_offset;

  LiChao(int min_x, int max_x, LinFunc first): min_x(min_x), max_x(max_x) {
    height = ceil_log2(max_x - min_x + 1) + 1;
    nodec = (1u << height) - 1;
    base_nodec = 1u << (height - 1);
    base_offset = (1u << (height - 1)) - 1;
    nodes.resize(nodec, first);
  }

  ll get(int x) {
    assert(min_x <= x && x <= max_x);
    auto num = x - min_x + base_offset + 1;
    auto result = nodes[num - 1](x);
    num /= 2;
    while(num >= 1) {
      // max daje maksimum, min - minimum
      result = max(result, nodes[num - 1](x));
      num /= 2;
    }
    return result;
  }

  void insert(LinFunc func) {
    auto descend = Y([&](auto &self, int num, int node_l, int node_r) -> void {
      auto x1 = min_x + node_l, x2 = min_x + node_r;
      // > daje maksimum, < - minimum
      auto a = func(x1) > nodes[num - 1](x1),
           b = func(x2) > nodes[num - 1](x2);
      if(a && b) {
        nodes[num - 1] = func;
      } else if(a || b) {
        auto mid = (node_l + node_r) / 2;
        self(2 * num, node_l, mid);
        self(2 * num + 1, mid + 1, node_r);
      }
    });
    descend(1, 0, base_nodec - 1);
  }
};
