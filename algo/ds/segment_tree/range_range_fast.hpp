/*
 * Szybsza implementacja drzewa przedziałowego przedział-przedział
 *                                          digitcrusher/algorytmy
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
 * Szybsza implementacja drzewa przedziałowego przedział-przedział -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego przedziału
 *   elementów (get) i modyfikacji (modify) w O(log n). Ta implementacja pozbywa
 *   się overheadu NodeOps.
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów. Sum musi być łączne, czyli
 *   Sum(Sum(a, b), c) = Sum(a, Sum(b, c)).
 * ApplyChange: (Value, Change, int) -> Value
 *   Aplikuje zmianę na wartość sumy spójnego przedziału elementów o rozmiarze
 *   będącym potęgą dwójki.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 */
template<
  class Value,
  class Sum,
  class Change,
  class ApplyChange,
  class MergeChange
> struct SegmentTree {
  Sum sum;
  ApplyChange apply_change;
  MergeChange merge_change;

  struct Node {
    Value val;
    Change latent_change;
    bool has_change = false;
  };

  int elemc;
  vector<Node> nodes;

  int height, nodec;
  int base_nodec, base_offset;

  SegmentTree(vector<Value> const& elems, Sum sum = Sum(),
              ApplyChange apply_change = ApplyChange(),
              MergeChange merge_change = MergeChange()):
    elemc(elems.size()), sum(sum), apply_change(apply_change), merge_change(merge_change)
  {
    height = ceil_log2(elemc) + 1;
    nodec = (1u << height) - 1;
    base_nodec = 1u << (height - 1);
    base_offset = (1u << (height - 1)) - 1;
    nodes.resize(nodec);

    for(auto i: v::iota(0, elemc)) {
      nodes[base_offset + i].val = elems[i];
    }
    resum(0, elemc - 1);
  }

  Value get(int l, int r) {
    assert(0 <= l && l <= r && r < elemc);
    auto descend = Y([&](auto &self, int num, int node_l, int node_r) -> Value {
      if(is_in(node_l, node_r, l, r)) {
        return nodes[num - 1].val;
      } else {
        propagate_change(num, node_l, node_r);
        auto mid = (node_l + node_r) / 2;
        if(!do_intersect(mid + 1, node_r, l, r)) {
          return self(2 * num, node_l, mid);
        } else if(!do_intersect(node_l, mid, l, r)) {
          return self(2 * num + 1, mid + 1, node_r);
        } else {
          return sum(self(2 * num, node_l, mid), self(2 * num + 1, mid + 1, node_r));
        }
      }
    });
    return descend(1, 0, base_nodec - 1);
  }

  void modify(int l, int r, Change change) {
    assert(0 <= l && l <= r && r < elemc);
    auto descend = Y([&](auto &self, int num, int node_l, int node_r) -> void {
      if(is_in(node_l, node_r, l, r)) {
        receive_change(num, node_l, node_r, change);
      } else {
        propagate_change(num, node_l, node_r);
        auto mid = (node_l + node_r) / 2;
        if(do_intersect(node_l, mid, l, r)) {
          self(2 * num, node_l, mid);
        }
        if(do_intersect(mid + 1, node_r, l, r)) {
          self(2 * num + 1, mid + 1, node_r);
        }
        if(node_r < elemc) {
          nodes[num - 1].val = sum(nodes[2 * num - 1].val, nodes[2 * num].val);
        }
      }
    });
    descend(1, 0, base_nodec - 1);
  }

  void resum(int l, int r) {
    assert(0 <= l && l <= r && r < elemc);
    auto descend = Y([&](auto &self, int num, int node_l, int node_r) -> void {
      if(node_l == node_r) return;
      auto &node = nodes[num - 1];
      auto mid = (node_l + node_r) / 2;

      // Nie propagujemy zmian do wierzchołków w całości w [l, r].
      if(node.has_change) {
        node.has_change = false;

        if(!is_in(node_l, mid, l, r)) {
          receive_change(2 * num, node_l, mid, node.latent_change);
        }
        if(!is_in(mid + 1, node_r, l, r) && mid + 1 < elemc) {
          receive_change(2 * num + 1, mid + 1, node_r, node.latent_change);
        }
      }

      if(do_intersect(node_l, mid, l, r)) {
        self(2 * num, node_l, mid);
      }
      if(do_intersect(mid + 1, node_r, l, r)) {
        self(2 * num + 1, mid + 1, node_r);
      }
      if(node_r < elemc) {
        node.val = sum(nodes[2 * num - 1].val, nodes[2 * num].val);
      }
    });
    descend(1, 0, base_nodec - 1);
  }

  void receive_change(int num, int node_l, int node_r, Change change) {
    auto &node = nodes[num - 1];
    // Nie aktualizujemy wierzchołków z elementami spoza tablicy.
    if(node_r < elemc) {
      node.val = apply_change(node.val, change, node_r - node_l + 1);
    }
    if(node_l != node_r) {
      node.latent_change = node.has_change ? merge_change(node.latent_change, change) : change;
      node.has_change = true;
    }
  }

  void propagate_change(int num, int node_l, int node_r) {
    auto &node = nodes[num - 1];
    if(!node.has_change) return;
    node.has_change = false;

    if(node_l != node_r) {
      auto mid = (node_l + node_r) / 2;
      receive_change(2 * num, node_l, mid, node.latent_change);
      if(mid + 1 < elemc) {
        receive_change(2 * num + 1, mid + 1, node_r, node.latent_change);
      }
    }
  }
};
