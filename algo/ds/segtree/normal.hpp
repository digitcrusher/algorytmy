/*
 * Drzewo przedziałowe przedział-przedział - digitcrusher/algorytmy
 *
 * Copyright (c) 2021 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/int.hpp"
#include "misc.hpp"
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

/*
 * Drzewo przedziałowe przedział-przedział -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego przedziału
 *   elementów (get) i modyfikacji (modify) w czasie logarytmicznym.
 *
 * Ta implementacja:
 * - jest zgodna z C++11;
 * - używa int zamiast size_t do indeksowania elementów; oraz
 * - zakłada, że sum(Value(), Value()) == Value() przy tworzeniu pustego drzewa.
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów. Sum musi być łączne, czyli
 *   sum(sum(a, b), c) = sum(a, sum(b, c)).
 * ApplyChange: (Value, Change, int) -> Value
 *   Aplikuje zmianę na wartość sumy spójnego przedziału elementów o rozmiarze
 *   będącym potęgą dwójki.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 */
template<class Value, class Change>
struct DefaultApplyChange {
  Value operator()(Value const& val,
                   Change const& change __attribute__((unused)),
                   int elemc __attribute__((unused)))
  {
    return val;
  };
};

template<class Change>
struct DefaultMergeChange {
  Change operator()(Change const& a,
                    Change const& b __attribute__((unused)))
  {
    return b;
  }
};

template<
  class Value,
  class Sum,
  class Change = tuple<>,
  class ApplyChange = DefaultApplyChange<Value, Change>,
  class MergeChange = DefaultMergeChange<Change>
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

  int elemc = 0;
  vector<Node> nodes;

  SegTree(Sum const& sum = Sum(),
          ApplyChange const& apply_change = ApplyChange(),
          MergeChange const& merge_change = MergeChange()):
    sum(sum), apply_change(apply_change), merge_change(merge_change) {}

  SegTree(int cnt, Value const& val,
          Sum const& sum = Sum(),
          ApplyChange const& apply_change = ApplyChange(),
          MergeChange const& merge_change = MergeChange()):
    SegTree(sum, apply_change, merge_change)
  {
    assign(cnt, val);
  }

  template<class InputIt, class = require_input_iter<InputIt>>
  SegTree(InputIt first, InputIt end,
          Sum const& sum = Sum(),
          ApplyChange const& apply_change = ApplyChange(),
          MergeChange const& merge_change = MergeChange()):
    SegTree(sum, apply_change, merge_change)
  {
    assign(first, end);
  }

  SegTree(initializer_list<Value> elems,
          Sum const& sum = Sum(),
          ApplyChange const& apply_change = ApplyChange(),
          MergeChange const& merge_change = MergeChange()):
    SegTree(sum, apply_change, merge_change)
  {
    assign(elems);
  }

  int size() {
    return elemc;
  }
  bool empty() {
    return elemc == 0;
  }

  void assign(int cnt, Value const& val) {
    elemc = cnt;
    nodes.clear();
    nodes.resize(nodec(), {val});
    if(elemc > 0) {
      root().resum();
    }
  }
  template<class InputIt, class = require_input_iter<InputIt>>
  void assign(InputIt first, InputIt end) {
    elemc = std::distance(first, end);
    nodes.clear();
    nodes.resize(nodec());
    std::copy(first, end, nodes.end() - base_nodec());
    if(elemc > 0) {
      root().resum();
    }
  }
  void assign(initializer_list<Value> elems) {
    assign(elems.begin(), elems.end());
  }
  void clear() {
    elemc = 0;
    nodes.clear();
  }
  void swap(SegTree &other) {
    swap(sum, other.sum);
    swap(apply_change, other.apply_change);
    swap(merge_change, other.merge_change);
    swap(elemc, other.elemc);
    swap(nodes, other.nodes);
  }
  SegTree& operator=(initializer_list<Value> elems) {
    assign(elems);
    return *this;
  }

  int height() {
    return elemc == 0 ? 0 : ceil_log2(elemc) + 1;
  }
  int level_nodec(int level) {
    return 1u << level;
  }
  int level_offset(int level) {
    return (1u << level) - 1;
  }

  int nodec() {
    return level_offset(height());
  }
  int base_nodec() {
    return level_nodec(height() - 1);
  }
  int base_offset() {
    return level_offset(height() - 1);
  }

  NodeOps root() {
    assert(elemc >= 1);
    return NodeOps(1, *this);
  }
  Value get(int l, int r) {
    assert(l <= r);
    assert(l < elemc);
    assert(r < elemc);
    return root().get(l, r);
  }
  void modify(int l, int r, Change const& change) {
    assert(l <= r);
    assert(l < elemc);
    assert(r < elemc);
    root().modify(l, r, change);
  }
  void resum(int l, int r) {
    assert(l <= r);
    assert(l < elemc);
    assert(r < elemc);
    root().resum(l, r);
  }
  void resum(int idx) {
    resum(idx, idx);
  }
  void resum() {
    resum(0, elemc - 1);
  }

  /*
   * Node nie ma dostępu do drzewa z jego metod, a referencja do drzewa
   * w każdym wierzchołku byłaby za bardzo kosztowna pamięciowo.
   */
  struct NodeOps {
    int const num;
    SegTree &tree;
    Node &node;

    int const level, elemc, l, r;
    bool const has_children;

    NodeOps(int num, SegTree &tree):
      num(num), tree(tree), node(tree.nodes[num - 1]),
      level(floor_log2(num)),
      elemc(tree.base_nodec() >> level),
      l((num - 1 - tree.level_offset(level)) * elemc),
      r(l + elemc - 1),
      has_children(l != r) {}

    NodeOps parent() {
      assert(level > 0);
      return NodeOps(num / 2, tree);
    }
    NodeOps left() {
      assert(level < tree.height() - 1);
      return NodeOps(num * 2, tree);
    }
    NodeOps right() {
      assert(level < tree.height() - 1);
      return NodeOps(num * 2 + 1, tree);
    }

    bool is_in(int l, int r) {
      return l <= this->l && this->r <= r;
    }
    bool does_intersect(int l, int r) {
      return !(l > this->r || r < this->l);
    }

    void receive_change(Change const& change) {
      /*
       * Nie powinny nas nigdy interesować wierzchołki
       * z przedziałem niezawierającym elementy z tablicy.
       */
      assert(l < tree.elemc);

      /*
       * Nie chcemy marnować czasu na aktualizowanie wartości wierzchołka
       * z przedziałem zawierającym elementy spoza tablicy.
       */
      if(r < tree.elemc) {
        node.val = tree.apply_change(node.val, change, elemc);
      }
      if(has_children) {
        node.latent_change = node.has_change ? tree.merge_change(node.latent_change, change) : change;
        node.has_change = true;
      }
    }
    void propagate_change(bool should_recurse = false) {
      assert(l < tree.elemc);

      if(node.has_change) {
        node.has_change = false;

        if(has_children) {
          left().receive_change(node.latent_change);
          /*
           * Nie chcemy marnować czasu na aktualizowanie prawego dziecka, jeśli
           * jego przedział nie zawiera żadnych elementów tablicy. Nie musimy
           * robić ifa dla lewego dziecka, bo na pewno zawiera jakieś elementy
           * z tablicy, jeśli obecny wierzchołek też zawiera jakieś, co na pewno
           * jest prawdą, skoro powyższy assert nie został naruszony.
           */
          if(right().l < tree.elemc) {
            right().receive_change(node.latent_change);
          }
        }
      }

      if(has_children && should_recurse) {
        left().propagate_change(true);
        if(right().l < tree.elemc) {
          right().propagate_change(true);
        }
      }
    }

    Value get(int l, int r) {
      assert(does_intersect(l, r));
      assert(this->l < tree.elemc);

      if(is_in(l, r)) {
        return node.val;
      } else {
        propagate_change();
        if(!right().does_intersect(l, r)) {
          return left().get(l, r);
        } else if(!left().does_intersect(l, r)) {
          /*
           * Poprawne zapytanie o modyfikacje nigdy nie zejdzie do prawego
           * dziecka, jeśli nie zawiera żadnych elementów tablicy. Poniższy
           * assert to sanity check.
           */
          assert(right().l < tree.elemc);
          return right().get(l, r);
        } else {
          assert(right().l < tree.elemc);
          return tree.sum(left().get(l, r), right().get(l, r));
        }
      }
    }

    void modify(int l, int r, Change const& change) {
      assert(does_intersect(l, r));
      assert(this->l < tree.elemc);

      if(is_in(l, r)) {
        receive_change(change);
      } else {
        propagate_change();
        if(left().does_intersect(l, r)) {
          left().modify(l, r, change);
        }
        if(right().does_intersect(l, r)) {
          assert(right().l < tree.elemc);
          right().modify(l, r, change);
        }
        /*
         * Poprawne zapytanie o sumę przedziału nigdy nie weźmie wartości
         * obecnego wierzchołka, jeśli jego przedział nie zawiera się w tablicy.
         */
        if(this->r < tree.elemc) {
          node.val = tree.sum(left().node.val, right().node.val);
        }
      }
    }

    void resum(int l, int r) {
      assert(does_intersect(l, r));
      assert(this->l < tree.elemc);

      if(has_children) {
        /*
         * Propagujemy zmiany tak, aby wierzchołki
         * w całości w [l, r] nie zostały zmienione.
         */
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
          assert(right().l < tree.elemc);
          right().resum(l, r);
        }
        if(this->r < tree.elemc) {
          node.val = tree.sum(left().node.val, right().node.val);
        }
      }
    }
    void resum(int idx) {
      resum(idx, idx);
    }
    void resum() {
      resum(0, tree.elemc - 1);
    }
  };
};
