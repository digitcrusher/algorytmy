/*
 * Drzewo przedziałowe punkt-przedział 2D - digitcrusher/algorytmy
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
#include <functional>
#include <vector>

/*
 * Drzewo przedziałowe punkt-przedział 2D -
 *   Struktura danych wspierająca operacje obliczenia sumy podmacierzy elementów
 *   (get) i ustawienia elementu (set) w O(log w * log h). Zużywa O(w * h)
 *   pamięci. Ta implementacja zakłada, że początkowa tablica nigdy nie
 *   jest pusta, oraz sumuje domyślnie zainicjalizowane wartości.
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwie sąsiednie podmacierze elementów. Sum musi być łączne
 *   i przemienne, czyli:
 *   - Sum(Sum(a, b), c) = Sum(a, Sum(b, c))
 *   - Sum(a, b) = Sum(b, a)
 */
template<class Value, class Sum>
struct SegmentTreePointRange2D {
  Sum sum;

  int w, h;
  vector<vector<Value>> nodes;

  int x_height, x_nodec;
  int y_height, y_nodec;
  int x_base_offset;
  int y_base_offset;

  SegmentTreePointRange2D(vector<vector<Value>> const& elems, Sum sum = Sum()):
    w(elems[0].size()), h(elems.size()), sum(sum)
  {
    x_height = ceil_log2(w) + 1;
    y_height = ceil_log2(h) + 1;
    x_nodec = (1u << x_height) - 1;
    y_nodec = (1u << y_height) - 1;
    x_base_offset = (1u << (x_height - 1)) - 1;
    y_base_offset = (1u << (y_height - 1)) - 1;
    nodes.resize(y_nodec, vector(x_nodec));

    for(int y = 0; y < h; y++) {
      for(int x = 0; x < w; x++) {
        nodes[y_base_offset + y][x_base_offset + x] = elems[y][x];
      }
    }
    resum();
  }

  Value get(int x1, int y1, int x2, int y2) {
    assert(0 <= x1 && x1 <= x2 && x2 < w);
    assert(0 <= y1 && y1 <= y2 && y2 < h);

    auto get_x = [&](int y, int x1, int x2) {
      Value left{}, right{};
      x1 += x_base_offset + 1;
      x2 += x_base_offset + 1;
      while(x1 <= x2) {
        if(x1 % 2 == 1) {
          left = sum(left, nodes[y - 1][x1 - 1]);
          x1++;
        }
        if(x2 % 2 == 0) {
          right = sum(nodes[y - 1][x2 - 1], right);
          x2--;
        }
        x1 /= 2, x2 /= 2;
      }
      return sum(left, right);
    };

    Value top{}, bottom{};
    y1 += y_base_offset + 1;
    y2 += y_base_offset + 1;
    while(y1 <= y2) {
      if(y1 % 2 == 1) {
        top = sum(top, get_x(y1, x1, x2));
        y1++;
      }
      if(y2 % 2 == 0) {
        bottom = sum(get_x(y2, x1, x2), bottom);
        y2--;
      }
      y1 /= 2, y2 /= 2;
    }
    return sum(top, bottom);
  }

  void set(int x, int y, Value val) {
    assert(0 <= x && x < w);
    assert(0 <= y && y < h);
    x += x_base_offset + 1;
    y += y_base_offset + 1;
    nodes[y - 1][x - 1] = val;
    for(int i = x / 2; i >= 1; i /= 2) {
      nodes[y - 1][i - 1] = sum(nodes[y - 1][2 * i - 1], nodes[y - 1][2 * i]);
    }
    y /= 2;
    while(y >= 1) {
      for(int i = x; i >= 1; i /= 2) {
        nodes[y - 1][i - 1] = sum(nodes[2 * y - 1][i - 1], nodes[2 * y][i - 1]);
      }
      y /= 2;
    }
  }

  void resum(int y_num = 1) {
    if(y_num - 1 < y_base_offset) {
      resum(2 * y_num);
      resum(2 * y_num + 1);
    }
    function<void(int)> resum_x = [&](int x_num) {
      if(x_num - 1 < x_base_offset) {
        resum_x(2 * x_num);
        resum_x(2 * x_num + 1);
      }
      if(y_num - 1 < y_base_offset) {
        nodes[y_num - 1][x_num - 1] = sum(nodes[2 * y_num - 1][x_num - 1], nodes[2 * y_num][x_num - 1]);
      } else if(x_num - 1 < x_base_offset) {
        nodes[y_num - 1][x_num - 1] = sum(nodes[y_num - 1][2 * x_num - 1], nodes[y_num - 1][2 * x_num]);
      }
    };
    resum_x(1);
  }
};
