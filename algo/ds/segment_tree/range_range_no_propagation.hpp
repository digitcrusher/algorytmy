/*
 * Drzewo przedziałowe przedział-przedział bez propagacji
 *                                 digitcrusher/algorytmy
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
 * Drzewo przedziałowe przedział-przedział bez propagacji -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego przedziału
 *   elementów (get) i modyfikacji (modify) w O(log n). Zużywa O(n) pamięci.
 *   Ta implementacja zakłada, że początkowa tablica nigdy nie jest pusta.
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów.
 * ApplyChange: (Value, Change, int) -> Value
 *   Aplikuje zmianę na wartość sumy spójnego przedziału elementów.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 *
 * Powyższe operacje muszą spełniać poniższe własności:
 * - Sum(Sum(a, b), c) = Sum(a, Sum(b, c)) - Sum jest łączne.
 * - ApplyChange(Sum(x, y), a, n) = Sum(ApplyChange(x, a, n), y) = Sum(x, ApplyChange(y, a, n))
 * - (i, j > 0 & i + j = n) => ApplyChange(Sum(x, y), a, n) = Sum(ApplyChange(x, a, i), ApplyChange(y, a, j))
 * - ApplyChange(x, MergeChange(a, b), n) = ApplyChange(ApplyChange(x, a, n), b, n)
 */
template<
  class Value,
  class Sum,
  class Change,
  class ApplyChange,
  class MergeChange
> struct SegmentTreeNoPropagation {
  Sum sum;
  ApplyChange apply_change;
  MergeChange merge_change;

  struct Node {
    Value val;
    Change change;
    bool has_change = false;
  };

  int elemc;
  vector<Node> nodes;

  int height, nodec;
  int base_nodec, base_offset;

  SegmentTreeNoPropagation(vector<Value> const& elems, Sum sum = Sum(),
                           ApplyChange apply_change = ApplyChange(),
                           MergeChange merge_change = MergeChange()):
    elemc(elems.size()), sum(sum), apply_change(apply_change), merge_change(merge_change)
  {
    height = ceil_log2(elemc) + 1;
    nodec = (1u << height) - 1;
    base_nodec = 1u << (height - 1);
    base_offset = (1u << (height - 1)) - 1;
    nodes.resize(nodec);

    for(int i = 0; i < elemc; i++) {
      nodes[base_offset + i].val = elems[i];
    }
    resum(0, elemc - 1);
  }

  Value get(int l, int r) {
    assert(0 <= l && l <= r && r < elemc);
    function<Value(int, int, int)> descend = [&](int num, int node_l, int node_r) {
      auto &node = nodes[num - 1];
      if(is_in(node_l, node_r, l, r)) {
        return node.val;
      } else {
        Value result;
        int mid = (node_l + node_r) / 2;
        if(!do_intersect(mid + 1, node_r, l, r)) {
          result = descend(2 * num, node_l, mid);
        } else if(!do_intersect(node_l, mid, l, r)) {
          result = descend(2 * num + 1, mid + 1, node_r);
        } else {
          result = sum(descend(2 * num, node_l, mid), descend(2 * num + 1, mid + 1, node_r));
        }
        if(node.has_change) {
          result = apply_change(result, node.change, min(r, node_r) - max(l, node_l) + 1);
        }
        return result;
      }
    };
    return descend(1, 0, base_nodec - 1);
  }

  void modify(int l, int r, Change change) {
    assert(0 <= l && l <= r && r < elemc);
    function<void(int, int, int)> descend = [&](int num, int node_l, int node_r) {
      if(is_in(node_l, node_r, l, r)) {
        receive_change(num, node_l, node_r, change);
      } else {
        int mid = (node_l + node_r) / 2;
        if(do_intersect(node_l, mid, l, r)) {
          descend(2 * num, node_l, mid);
        }
        if(do_intersect(mid + 1, node_r, l, r)) {
          descend(2 * num + 1, mid + 1, node_r);
        }
        if(node_r < elemc) {
          nodes[num - 1].val = apply_change(nodes[num - 1].val, change, min(r, node_r) - max(l, node_l) + 1);
        }
      }
    };
    descend(1, 0, base_nodec - 1);
  }

  void resum(int l, int r) {
    assert(0 <= l && l <= r && r < elemc);
    function<void(int, int, int)> descend = [&](int num, int node_l, int node_r) {
      if(node_l == node_r) return;
      auto &node = nodes[num - 1];
      int mid = (node_l + node_r) / 2;

      // Nie propagujemy zmian do wierzchołków w całości w [l, r].
      if(node.has_change) {
        node.has_change = false;

        if(!is_in(node_l, mid, l, r)) {
          receive_change(2 * num, node_l, mid, node.change);
        }
        if(!is_in(mid + 1, node_r, l, r) && mid + 1 < elemc) {
          receive_change(2 * num + 1, mid + 1, node_r, node.change);
        }
      }

      if(do_intersect(node_l, mid, l, r)) {
        descend(2 * num, node_l, mid);
      }
      if(do_intersect(mid + 1, node_r, l, r)) {
        descend(2 * num + 1, mid + 1, node_r);
      }
      if(node_r < elemc) {
        node.val = sum(nodes[2 * num - 1].val, nodes[2 * num].val);
      }
    };
    descend(1, 0, base_nodec - 1);
  }

  bool is_in(int a1, int a2, int b1, int b2) {
    return b1 <= a1 && a2 <= b2;
  }
  bool do_intersect(int a1, int a2, int b1, int b2) {
    return !(a2 < b1 || b2 < a1);
  }

  void receive_change(int num, int node_l, int node_r, Change change) {
    auto &node = nodes[num - 1];
    // Nie aktualizujemy wierzchołków z elementami spoza tablicy.
    if(node_r < elemc) {
      node.val = apply_change(node.val, change, node_r - node_l + 1);
    }
    if(node_l != node_r) {
      node.change = node.has_change ? merge_change(node.change, change) : change;
      node.has_change = true;
    }
  }
};
