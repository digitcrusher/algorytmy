/*
 * Drzewo przedziałowe przedział-przedział - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
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
 * Drzewo przedziałowe przedział-przedział -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego przedziału
 *   elementów (get) i modyfikacji (modify) w O(log n). Zużywa O(n) pamięci.
 *   Ta implementacja zakłada, że początkowa tablica nigdy nie jest pusta.
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
  struct NodeOps;

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
    nodec = level_offset(height);
    base_nodec = level_nodec(height - 1);
    base_offset = level_offset(height - 1);
    nodes.resize(nodec);

    for(int i = 0; i < elemc; i++) {
      nodes[base_offset + i].val = elems[i];
    }
    resum(0, elemc - 1);
  }

  int level_nodec(int level) {
    return 1u << level;
  }
  int level_offset(int level) {
    return (1u << level) - 1;
  }

  NodeOps root() {
    return NodeOps(1, *this);
  }
  Value get(int l, int r) {
    assert(l <= r && r < elemc);
    return root().get(l, r);
  }
  void modify(int l, int r, Change change) {
    assert(l <= r && r < elemc);
    root().modify(l, r, change);
  }
  void resum(int l, int r) {
    assert(l <= r && r < elemc);
    root().resum(l, r);
  }

  /*
   * Node nie ma dostępu do drzewa z jego metod, a referencja do drzewa
   * w każdym wierzchołku byłaby za bardzo kosztowna pamięciowo.
   */
  struct NodeOps {
    int num;
    SegmentTree &tree;
    Node &node;

    int level, elemc, l, r;
    bool has_children;

    NodeOps(int num, SegmentTree &tree):
      num(num), tree(tree), node(tree.nodes[num - 1])
    {
      level = floor_log2(num);
      elemc = tree.base_nodec >> level;
      l = (num - 1 - tree.level_offset(level)) * elemc;
      r = l + elemc - 1;
      has_children = l != r;
    }

    NodeOps left() {
      return NodeOps(num * 2, tree);
    }
    NodeOps right() {
      return NodeOps(num * 2 + 1, tree);
    }

    bool is_in(int l, int r) {
      return l <= this->l && this->r <= r;
    }
    bool does_intersect(int l, int r) {
      return !(l > this->r || r < this->l);
    }

    void receive_change(Change change) {
      // Nie aktualizujemy wierzchołków z elementami spoza tablicy.
      if(r < tree.elemc) {
        node.val = tree.apply_change(node.val, change, elemc);
      }
      if(has_children) {
        node.latent_change = node.has_change ? tree.merge_change(node.latent_change, change) : change;
        node.has_change = true;
      }
    }
    void propagate_change() {
      if(!node.has_change) return;
      node.has_change = false;

      if(has_children) {
        left().receive_change(node.latent_change);
        if(right().l < tree.elemc) {
          right().receive_change(node.latent_change);
        }
      }
    }

    Value get(int l, int r) {
      if(is_in(l, r)) {
        return node.val;
      } else {
        propagate_change();
        if(!right().does_intersect(l, r)) {
          return left().get(l, r);
        } else if(!left().does_intersect(l, r)) {
          return right().get(l, r);
        } else {
          return tree.sum(left().get(l, r), right().get(l, r));
        }
      }
    }

    void modify(int l, int r, Change change) {
      if(is_in(l, r)) {
        receive_change(change);
      } else {
        propagate_change();
        if(left().does_intersect(l, r)) {
          left().modify(l, r, change);
        }
        if(right().does_intersect(l, r)) {
          right().modify(l, r, change);
        }
        if(this->r < tree.elemc) {
          node.val = tree.sum(left().node.val, right().node.val);
        }
      }
    }

    void resum(int l, int r) {
      if(!has_children) return;

      // Nie propagujemy zmian do wierzchołków w całości w [l, r].
      if(node.has_change) {
        node.has_change = false;

        if(!left().is_in(l, r)) {
          left().receive_change(node.latent_change);
        }
        if(!right().is_in(l, r) && right().l < tree.elemc) {
          right().receive_change(node.latent_change);
        }
      }

      if(left().does_intersect(l, r)) {
        left().resum(l, r);
      }
      if(right().does_intersect(l, r)) {
        right().resum(l, r);
      }
      if(this->r < tree.elemc) {
        node.val = tree.sum(left().node.val, right().node.val);
      }
    }
  };
};
