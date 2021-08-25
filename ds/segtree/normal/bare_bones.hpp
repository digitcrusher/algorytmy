/*
 * Okrojona implementacja drzewa przedziałowego przedział-przedział
 *                                           digitcrusher/algorytmy
 *
 * Copyright (c) 2021 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include <vector>

/*
 * Okrojona implementacja drzewa przedziałowego przedział-przedział -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego przedziału
 *   elementów (get) i modyfikacji (modify) w czasie logarytmicznym.
 *
 * Ta implementacja:
 * - jest zgodna z C++11;
 * - nie jest const-correct;
 * - zakłada, że sum(Value(), Value()) == Value() przy tworzeniu wierzchołkow;
 * - zakłada, że drzewo nigdy nie jest puste;
 * - używa int zamiast size_t do indeksowania elementów; oraz
 * - jest przydatna do wkuwania na zawody.
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów. Sum musi być łączne, czyli
 *   (a sum b) sum c = a sum (b sum c).
 * ApplyChange: (Value, Change, int) -> Value
 *   Aplikuje zmianę na wartość sumy spójnego przedziału elementów o rozmiarze
 *   będącym potęgą dwójki.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 */
int floor_log2(int a) {
  return sizeof(int) * 8 - __builtin_clzll(a) - 1;
}
int ceil_log2(int a) {
  return a == 1 ? 0 : sizeof(int) * 8 - __builtin_clzll(a - 1);
}

template<
  class Value,
  class Sum,
  class Change,
  class ApplyChange,
  class MergeChange
> struct SegTree {
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
  std::vector<Node> nodes;

  int height, nodec;
  int base_nodec, base_offset;

  SegTree(int cnt): elemc(cnt) {
    height = ceil_log2(elemc) + 1;
    nodec = level_offset(height);
    base_nodec = level_nodec(height - 1);
    base_offset = level_offset(height - 1);

    nodes.resize(nodec);
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
    return root().get(l, r);
  }
  void modify(int l, int r, Change change) {
    root().modify(l, r, change);
  }

  struct NodeOps {
    int num;
    SegTree &tree;
    Node &node;

    int level, elemc, l, r;
    bool has_children;

    NodeOps(int num, SegTree &tree):
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
      node.val = tree.apply_change(node.val, change, elemc);
      node.latent_change = node.has_change ? tree.merge_change(node.latent_change, change) : change;
      node.has_change = true;
    }
    void propagate_change() {
      if(node.has_change) {
        node.has_change = false;

        if(has_children) {
          left().receive_change(node.latent_change);
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
        node.val = tree.sum(left().node.val, right().node.val);
      }
    }

    void resum(int l, int r) {
      if(has_children) {
        if(node.has_change) {
          node.has_change = false;

          if(!left().is_in(l, r)) {
            left().receive_change(node.latent_change);
          }
          if(!right().is_in(l, r)) {
            right().receive_change(node.latent_change);
          }
        }

        if(left().does_intersect(l, r)) {
          left().resum(l, r);
        }
        if(right().does_intersect(l, r)) {
          right().resum(l, r);
        }
        node.val = tree.sum(left().node.val, right().node.val);
      }
    }
  };
};
