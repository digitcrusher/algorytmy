/*
 * Drzewo przedziałowe przedział-przedział 2D - digitcrusher/algorytmy
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
 * Drzewo przedziałowe przedział-przedział 2D -
 *   Struktura danych wspierająca operacje obliczenia sumy podmacierzy
 *   elementów (get) i modyfikacji (modify) w O(log w * log h).
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwie sąsiednie podmacierze elementów.
 * ApplyChange: (Value, Change, int) -> Value
 *   Wielokrotnie aplikuje zmianę jednego elementu na podmacierz elementów.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 * MultiplyChange: (Change, int) -> Change
 *   Wielokrotnie kumuluje zmianę ze sobą.
 *
 * Powyższe operacje muszą spełniać poniższe własności:
 * - Sum(Sum(a, b), c) = Sum(a, Sum(b, c)) - Sum jest łączne.
 * - ApplyChange(Sum(x, y), a, n) = Sum(ApplyChange(x, a, n), y) = Sum(x, ApplyChange(y, a, n))
 * - (i, j > 0 & i + j = n) => ApplyChange(Sum(x, y), a, n) = Sum(ApplyChange(x, a, i), ApplyChange(y, a, j))
 * - ApplyChange(x, MergeChange(a, b), n) = ApplyChange(ApplyChange(x, a, n), b, n)
 * - ApplyChange(a, MultiplyChange(b, n), m) = ApplyChange(a, b, n * m)
 */
template<
  class Value,
  class Sum,
  class Change,
  class ApplyChange,
  class MergeChange,
  class MultiplyChange
> struct SegmentTree2D {
  Sum sum;
  ApplyChange apply_change;
  MergeChange merge_change;
  MultiplyChange multiply_change;

  struct Node {
    Value val;
    Change change_x, change_y, change_xy;
    bool has_change = false;
  };

  int w, h;
  vector<vector<Node>> nodes;

  int x_height, x_nodec;
  int y_height, y_nodec;
  int x_base_nodec, x_base_offset;
  int y_base_nodec, y_base_offset;

  SegmentTree2D(vector<vector<Value>> const& elems, Sum sum = {},
                ApplyChange apply_change = {},
                MergeChange merge_change = {},
                MultiplyChange multiply_change = {}):
    w(elems[0].size()), h(elems.size()), sum(sum),
    apply_change(apply_change), merge_change(merge_change), multiply_change(multiply_change)
  {
    x_height = ceil_log2(w) + 1;
    y_height = ceil_log2(h) + 1;
    x_nodec = (1u << x_height) - 1;
    y_nodec = (1u << y_height) - 1;
    x_base_nodec = 1u << (x_height - 1);
    y_base_nodec = 1u << (y_height - 1);
    x_base_offset = (1u << (x_height - 1)) - 1;
    y_base_offset = (1u << (y_height - 1)) - 1;
    nodes.resize(y_nodec, vector<Node>(x_nodec));

    for(auto y: v::iota(0, h)) {
      for(auto x: v::iota(0, w)) {
        nodes[y_base_offset + y][x_base_offset + x].val = elems[y][x];
      }
    }
    resum();
  }

  SegmentTree2D(int w, int h, Value zero, Sum sum = {},
                ApplyChange apply_change = {},
                MergeChange merge_change = {},
                MultiplyChange multiply_change = {}):
    w(w), h(h), sum(sum),
    apply_change(apply_change), merge_change(merge_change), multiply_change(multiply_change)
  {
    x_height = ceil_log2(w) + 1;
    y_height = ceil_log2(h) + 1;
    x_nodec = (1u << x_height) - 1;
    y_nodec = (1u << y_height) - 1;
    x_base_nodec = 1u << (x_height - 1);
    y_base_nodec = 1u << (y_height - 1);
    x_base_offset = (1u << (x_height - 1)) - 1;
    y_base_offset = (1u << (y_height - 1)) - 1;
    nodes.resize(y_nodec, vector(x_nodec, Node{ .val = zero }));
  }

  int overlap_of(int a1, int a2, int b1, int b2) {
    return max(0, min(a2, b2) - max(a1, b1) + 1);
  }

  Value get(int x1, int y1, int x2, int y2) {
    assert(0 <= x1 && x1 <= x2 && x2 < w);
    assert(0 <= y1 && y1 <= y2 && y2 < h);

    auto descend_x_for_val = Y([&](auto &self, int x_num, int y_num, int node_x1, int node_x2) -> Value {
      auto &node = nodes[y_num - 1][x_num - 1];
      if(is_in(node_x1, node_x2, x1, x2)) {
        return node.val;
      } else {
        Value result;
        auto mid = (node_x1 + node_x2) / 2;
        if(!do_intersect(mid + 1, node_x2, x1, x2)) {
          result = self(2 * x_num, y_num, node_x1, mid);
        } else if(!do_intersect(node_x1, mid, x1, x2)) {
          result = self(2 * x_num + 1, y_num, mid + 1, node_x2);
        } else {
          result = sum(
            self(2 * x_num, y_num, node_x1, mid),
            self(2 * x_num + 1, y_num, mid + 1, node_x2)
          );
        }

        if(node.has_change) {
          result = apply_change(result, node.change_x, overlap_of(x1, x2, node_x1, node_x2));
        }
        return result;
      }
    });

    auto descend_x_for_change = Y([&](auto &self, int x_num, int y_num, int node_x1, int node_x2) -> pair<Change, bool> {
      auto &node = nodes[y_num - 1][x_num - 1];
      if(is_in(node_x1, node_x2, x1, x2)) {
        return pair(node.change_y, node.has_change);
      } else {
        pair<Change, bool> result;
        result.second = false;

        auto mid = (node_x1 + node_x2) / 2;
        if(do_intersect(node_x1, mid, x1, x2)) {
          result = self(2 * x_num, y_num, node_x1, mid);
        }
        if(do_intersect(mid + 1, node_x2, x1, x2)) {
          auto other = self(2 * x_num + 1, y_num, mid + 1, node_x2);
          if(!result.second) {
            result = other;
          } else if(other.second) {
            result.first = merge_change(result.first, other.first);
          }
        }

        if(node.has_change) {
          auto change = multiply_change(node.change_xy, overlap_of(x1, x2, node_x1, node_x2));
          result.first = result.second ? merge_change(result.first, change) : change;
          result.second = true;
        }
        return result;
      }
    });

    auto descend_y = Y([&](auto &self, int y_num, int node_y1, int node_y2) -> Value {
      if(is_in(node_y1, node_y2, y1, y2)) {
        return descend_x_for_val(1, y_num, 0, x_base_nodec - 1);
      } else {
        Value result;
        auto mid = (node_y1 + node_y2) / 2;
        if(!do_intersect(mid + 1, node_y2, y1, y2)) {
          result = self(2 * y_num, node_y1, mid);
        } else if(!do_intersect(node_y1, mid, y1, y2)) {
          result = self(2 * y_num + 1, mid + 1, node_y2);
        } else {
          result = sum(self(2 * y_num, node_y1, mid), self(2 * y_num + 1, mid + 1, node_y2));
        }

        auto [change, has_change] = descend_x_for_change(1, y_num, 0, x_base_nodec - 1);
        if(has_change) {
          result = apply_change(result, change, overlap_of(y1, y2, node_y1, node_y2));
        }
        return result;
      }
    });

    return descend_y(1, 0, y_base_nodec - 1);
  }

  void modify(int x1, int y1, int x2, int y2, Change change) {
    assert(0 <= x1 && x1 <= x2 && x2 < w);
    assert(0 <= y1 && y1 <= y2 && y2 < h);

    auto descend_x = Y([&](auto &self, int x_num, int y_num, int node_x1, int node_y1, int node_x2, int node_y2) -> void {
      if(!is_in(node_x1, node_x2, x1, x2)) {
        auto mid = (node_x1 + node_x2) / 2;
        if(do_intersect(node_x1, mid, x1, x2)) {
          self(2 * x_num, y_num, node_x1, node_y1, mid, node_y2);
        }
        if(do_intersect(mid + 1, node_x2, x1, x2)) {
          self(2 * x_num + 1, y_num, mid + 1, node_y1, node_x2, node_y2);
        }
      }

      if(node_x2 >= w) return;
      auto overlap_x = overlap_of(x1, x2, node_x1, node_x2),
           overlap_y = overlap_of(y1, y2, node_y1, node_y2);
      auto is_x_covered = is_in(node_x1, node_x2, x1, x2) && node_x1 != node_x2,
           is_y_covered = is_in(node_y1, node_y2, y1, y2) && node_y1 != node_y2;
      auto &node = nodes[y_num - 1][x_num - 1];
      node.val = apply_change(node.val, change, overlap_x * overlap_y);

      // TODO: a node.has_change to gdzie????
      if(is_x_covered) {
        node.change_x = merge_change(node.change_x, multiply_change(change, overlap_y));
      }
      if(is_y_covered) {
        node.change_y = merge_change(node.change_y, multiply_change(change, overlap_x));
      }
      if(is_x_covered && is_y_covered) {
        node.change_xy = merge_change(node.change_xy, change);
      }
      if(is_x_covered || is_y_covered) {
        node.has_change = true;
      }
    });

    auto descend_y = Y([&](auto &self, int y_num, int node_y1, int node_y2) -> void {
      if(!is_in(node_y1, node_y2, y1, y2)) {
        auto mid = (node_y1 + node_y2) / 2;
        if(do_intersect(node_y1, mid, y1, y2)) {
          self(2 * y_num, node_y1, mid);
        }
        if(do_intersect(mid + 1, node_y2, y1, y2)) {
          self(2 * y_num + 1, mid + 1, node_y2);
        }
      }
      if(node_y2 < h) {
        descend_x(1, y_num, 0, node_y1, x_base_nodec - 1, node_y2);
      }
    });

    return descend_y(1, 0, y_base_nodec - 1);
  }

  void resum() {
    auto descend_x = Y([&](auto &self, int x_num, int y_num, int node_x1, int node_x2) -> void {
      if(node_x1 != node_x2) {
        auto mid = (node_x1 + node_x2) / 2;
        self(2 * x_num, y_num, node_x1, mid);
        self(2 * x_num + 1, y_num, mid + 1, node_x2);
      }

      if(node_x2 >= w) return;
      auto &node = nodes[y_num - 1][x_num - 1];
      if(y_num - 1 < y_base_offset) {
        node.val = sum(nodes[2 * y_num - 1][x_num - 1].val, nodes[2 * y_num][x_num - 1].val);
      } else if(node_x1 != node_x2) {
        node.val = sum(nodes[y_num - 1][2 * x_num - 1].val, nodes[y_num - 1][2 * x_num].val);
      }
      node.has_change = false;
    });

    auto descend_y = Y([&](auto &self, int y_num, int node_y1, int node_y2) -> void {
      if(node_y1 != node_y2) {
        auto mid = (node_y1 + node_y2) / 2;
        self(2 * y_num, node_y1, mid);
        self(2 * y_num + 1, mid + 1, node_y2);
      }
      if(node_y2 < h) {
        descend_x(1, y_num, 0, x_base_nodec - 1);
      }
    });

    descend_y(1, 0, y_base_nodec - 1);
  }
};
