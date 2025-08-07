/*
 * Drzewo przedziałowe przedział-przedział - digitcrusher/algorytmy
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
 * Drzewo przedziałowe przedział-przedział -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego
 *   przedziału elementów (get) i modyfikacji (modify) w O(log n).
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

  SegmentTree(vector<Value> const& elems, Sum sum = {},
              ApplyChange apply_change = {},
              MergeChange merge_change = {}):
    elemc(elems.size()), sum(sum), apply_change(apply_change), merge_change(merge_change)
  {
    height = bit_width(elemc - 1u) + 1;
    nodec = (1u << height) - 1;
    base_nodec = 1u << (height - 1);
    base_offset = (1u << (height - 1)) - 1;
    nodes.resize(nodec);

    for(auto i: v::iota(0, elemc)) {
      nodes[base_offset + i].val = elems[i];
    }
    resum(0, elemc - 1);
  }

  SegmentTree(int elemc, Value zero, Sum sum = {},
              ApplyChange apply_change = {},
              MergeChange merge_change = {}):
    elemc(elemc), sum(sum), apply_change(apply_change), merge_change(merge_change)
  {
    height = bit_width(elemc - 1u) + 1;
    nodec = (1u << height) - 1;
    base_nodec = 1u << (height - 1);
    base_offset = (1u << (height - 1)) - 1;
    nodes.resize(nodec, Node{ .val = zero });
  }

  Value get(int l, int r) {
    assert(0 <= l && l <= r && r < elemc);
    auto descend = Y([&](auto &self, int num, int node_l, int node_r) -> Value {
      if(l <= node_l && node_r <= r) {
        return nodes[num - 1].val;
      }

      propagate_change(num, node_l, node_r);
      auto mid = (node_l + node_r) / 2;
      if(r <= mid) {
        return self(2 * num, node_l, mid);
      } else if(mid + 1 <= l) {
        return self(2 * num + 1, mid + 1, node_r);
      } else {
        return sum(self(2 * num, node_l, mid), self(2 * num + 1, mid + 1, node_r));
      }
    });
    return descend(1, 0, base_nodec - 1);
  }

  void modify(int l, int r, Change change) {
    assert(0 <= l && l <= r && r < elemc);
    auto descend = Y([&](auto &self, int num, int node_l, int node_r) -> void {
      if(l <= node_l && node_r <= r) {
        receive_change(num, node_l, node_r, change);
        return;
      }

      propagate_change(num, node_l, node_r);
      auto mid = (node_l + node_r) / 2;
      if(l <= mid) {
        self(2 * num, node_l, mid);
      }
      if(mid + 1 <= r) {
        self(2 * num + 1, mid + 1, node_r);
      }
      if(node_r < elemc) {
        nodes[num - 1].val = sum(nodes[2 * num - 1].val, nodes[2 * num].val);
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

        if(!(l <= node_l && mid <= r)) {
          receive_change(2 * num, node_l, mid, node.latent_change);
        }
        if(!(l <= mid + 1 && node_r <= r) && mid + 1 < elemc) {
          receive_change(2 * num + 1, mid + 1, node_r, node.latent_change);
        }
      }

      if(l <= mid) {
        self(2 * num, node_l, mid);
      }
      if(mid + 1 <= r) {
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
