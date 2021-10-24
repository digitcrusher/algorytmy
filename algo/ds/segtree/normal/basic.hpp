/*
 * Podstawowa implementacja drzewa przedziałowego przedział-przedział
 *                                             digitcrusher/algorytmy
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
 * Podstawowa implementacja drzewa przedziałowego przedział-przedział -
 *   Struktura danych wspierająca operacje obliczenia sumy spójnego przedziału
 *   elementów (get) i modyfikacji (modify) w czasie logarytmicznym.
 *
 * Ta implementacja jest zgodna z C++11.
 *
 * Sum: (Value, Value) -> Value
 *   Łaczy dwa sąsiednie przedziały elementów. Sum musi być łączne, czyli
 *   (a sum b) sum c = a sum (b sum c).
 * ApplyChange: (Value, Change, size_t) -> Value
 *   Aplikuje zmianę na wartość sumy spójnego przedziału elementów o rozmiarze
 *   będącym potęgą dwójki.
 * MergeChange: (Change, Change) -> Change
 *   Kumuluje dwie zmiany do jednej.
 */
template<class Value, class Change>
struct DefaultApplyChange {
  Value operator()(Value const& val,
                   Change const& change __attribute__((unused)),
                   size_t elemc __attribute__((unused))) const
  {
    return val;
  };
};

template<class Change>
struct DefaultMergeChange {
  Change operator()(Change const& a,
                    Change const& b __attribute__((unused))) const
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
> struct SegmentTree {
  Sum sum;
  ApplyChange apply_change;
  MergeChange merge_change;

  struct Node {
    Value val;
    bool has_change = false;
    Change latent_change;

    Node() {}
    Node(Value val): val(val) {}
  };
  struct NodeOps;

  size_t elemc = 0;
  mutable vector<Node> nodes;

  NodeOps root_ops() const {
    assert(this->nodes.size() >= 1);
    return NodeOps(this->nodes[0], *this);
  }

  SegmentTree(Sum const& sum = Sum(),
              ApplyChange const& apply_change = ApplyChange(),
              MergeChange const& merge_change = MergeChange()):
    sum(sum), apply_change(apply_change), merge_change(merge_change) {}

  SegmentTree(size_t cnt, Value const& val,
              Sum const& sum = Sum(),
              ApplyChange const& apply_change = ApplyChange(),
              MergeChange const& merge_change = MergeChange()):
    SegmentTree(sum, apply_change, merge_change)
  {
    assign(cnt, val);
  }

  template<class InputIt, class = require_input_iter<InputIt>>
  SegmentTree(InputIt first, InputIt end,
              Sum const& sum = Sum(),
              ApplyChange const& apply_change = ApplyChange(),
              MergeChange const& merge_change = MergeChange()):
    SegmentTree(sum, apply_change, merge_change)
  {
    assign(first, end);
  }

  SegmentTree(initializer_list<Value> elems,
              Sum const& sum = Sum(),
              ApplyChange const& apply_change = ApplyChange(),
              MergeChange const& merge_change = MergeChange()):
    SegmentTree(sum, apply_change, merge_change)
  {
    assign(elems);
  }

  size_t size() const {
    return this->elemc;
  }
  size_t max_size() const {
    /*
     * Dodanie jeden do max_size wywołałoby overflow, jeśli
     * max_size vector'a to maksymalna wartość size_t.
     */
    return 1ull << floor_log2((this->nodes.max_size() - 1) + 1) - 1;
  }
  bool empty() const {
    return this->elemc == 0;
  }

  void swap(SegmentTree &other) {
    swap(this->sum, other.sum);
    swap(this->apply_change, other.apply_change);
    swap(this->merge_change, other.merge_change);
    swap(this->elemc, other.elemc);
    swap(this->nodes, other.nodes);
  }

  void clear() {
    this->elemc = 0;
    this->nodes.clear();
  }

  void assign(size_t cnt, Value const& val) {
    this->elemc = cnt;
    this->nodes.clear();
    this->nodes.resize(this->nodec(), Node(val));
    if(this->elemc > 0) {
      this->root_ops().resum();
    }
  }
  template<class InputIt, class = require_input_iter<InputIt>>
  void assign(InputIt first, InputIt end) {
    this->elemc = std::distance(first, end);
    this->nodes.clear();
    this->nodes.resize(this->nodec());
    std::copy(first, end, this->nodes.end() - this->base_nodec());
    if(this->elemc > 0) {
      this->root_ops().resum();
    }
  }
  void assign(initializer_list<Value> elems) {
    assign(elems.begin(), elems.end());
  }
  SegmentTree& operator=(initializer_list<Value> elems) {
    assign(elems);
    return *this;
  }

  Value get(size_t l, size_t r) const {
    assert(l <= r);
    assert(l < this->elemc);
    assert(r < this->elemc);
    return this->root_ops().get(l, r);
  }
  void modify(size_t l, size_t r, Change const& change) {
    assert(l <= r);
    assert(l < this->elemc);
    assert(r < this->elemc);
    this->root_ops().modify(l, r, change);
  }

  size_t height() const {
    return this->elemc == 0 ? 0 : ceil_log2(this->elemc) + 1;
  }
  size_t level_nodec(size_t level) const {
    return 1ull << level;
  }
  size_t level_offset(size_t level) const {
    return (1ull << level) - 1;
  }

  size_t nodec() const {
    return this->level_offset(this->height());
  }
  size_t base_nodec() const {
    return this->level_nodec(this->height() - 1);
  }
  size_t base_offset() const {
    return this->level_offset(this->height() - 1);
  }

  /*
   * Node nie ma dostępu do drzewa z jego metod, a referencja do drzewa
   * w każdym wierzchołku byłaby za bardzo kosztowna pamięciowo.
   */
  struct NodeOps {
    Node &node;
    SegmentTree const& tree;

    NodeOps(Node &node, SegmentTree const& tree): node(node), tree(tree) {}

    size_t num() const {
      return &node - &tree.nodes.front() + 1;
    }
    NodeOps parent() const {
      assert(this->level() > 0);
      return NodeOps(tree.nodes[this->num() / 2 - 1], tree);
    }
    NodeOps left() const {
      assert(this->level() < tree.height() - 1);
      return NodeOps(tree.nodes[this->num() * 2 - 1], tree);
    }
    NodeOps right() const {
      assert(this->level() < tree.height() - 1);
      return NodeOps(tree.nodes[this->num() * 2 + 1 - 1], tree);
    }
    size_t level() const {
      return floor_log2(this->num());
    }
    size_t elemc() const {
      return tree.base_nodec() >> this->level();
    }
    size_t l() const {
      return (this->num() - 1 - tree.level_offset(this->level())) * this->elemc();
    }
    size_t r() const {
      return this->l() + this->elemc() - 1;
    }
    bool has_children() const {
      return this->l() != this->r();
    }

    void receive_change(Change const& change) {
      /*
       * Nie powinny nas nigdy interesować wierzchołki
       * z przedziałem niezawierającym elementy z tablicy.
       */
      assert(this->l() < tree.elemc);

      /*
       * Nie chcemy marnować czasu na aktualizowanie wartości wierzchołka
       * z przedziałem zawierającym elementy spoza tablicy.
       */
      if(this->r() < tree.elemc) {
        node.val = tree.apply_change(node.val, change, this->elemc());
      }
      if(this->has_children()) {
        node.latent_change = node.has_change ? tree.merge_change(node.latent_change, change) : change;
        node.has_change = true;
      }
    }
    void propagate_change(bool should_recurse = false) {
      assert(this->l() < tree.elemc);

      if(node.has_change) {
        node.has_change = false;

        if(this->has_children()) {
          this->left().receive_change(node.latent_change);
          /*
           * Nie chcemy marnować czasu na aktualizowanie prawego dziecka, jeśli
           * jego przedział nie zawiera żadnych elementów tablicy. Nie musimy
           * robić ifa dla lewego dziecka, bo na pewno zawiera jakieś elementy
           * z tablicy, jeśli obecny wierzchołek też zawiera jakieś, co na pewno
           * jest prawdą, skoro powyższy assert nie został naruszony.
           */
          if(this->right().l() < tree.elemc) {
            this->right().receive_change(node.latent_change);
          }
        }
      }

      if(this->has_children() && should_recurse) {
        this->left().propagate_change(true);
        if(this->right().l() < tree.elemc) {
          this->right().propagate_change(true);
        }
      }
    }

    Value get(size_t l, size_t r) {
      assert(!(l > this->r()));
      assert(!(r < this->l()));
      assert(this->l() < tree.elemc);

      if(l <= this->l() && this->r() <= r) {
        return node.val;
      } else {
        propagate_change();
        if(r < this->right().l()) {
          return this->left().get(l, r);
        } else if(l > this->left().r()) {
          /*
           * Poprawne zapytanie o modyfikacje nigdy nie zejdzie do prawego
           * dziecka, jeśli nie zawiera żadnych elementów tablicy. Poniższy
           * assert to sanity check.
           */
          assert(this->right().l() < tree.elemc);
          return this->right().get(l, r);
        } else {
          assert(this->right().l() < tree.elemc);
          return tree.sum(this->left().get(l, r), this->right().get(l, r));
        }
      }
    }

    void modify(size_t l, size_t r, Change const& change) {
      assert(!(l > this->r()));
      assert(!(r < this->l()));
      assert(this->l() < tree.elemc);

      if(l <= this->l() && this->r() <= r) {
        receive_change(change);
      } else {
        propagate_change();
        if(!(l > this->left().r())) {
          this->left().modify(l, r, change);
        }
        if(!(r < this->right().l())) {
          assert(this->right().l() < tree.elemc);
          this->right().modify(l, r, change);
        }
        /*
         * Poprawne zapytanie o sumę przedziału nigdy nie weźmie wartości
         * obecnego wierzchołka, jeśli jego przedział nie zawiera się w tablicy.
         */
        if(this->r() < tree.elemc) {
          node.val = tree.sum(this->left().node.val, this->right().node.val);
        }
      }
    }

    void resum(size_t l, size_t r) {
      assert(!(l > this->r()));
      assert(!(r < this->l()));
      assert(this->l() < tree.elemc);

      if(this->has_children()) {
        /*
         * Propagujemy zmiany tak, aby wierzchołki
         * w całości w [l, r] nie zostały zmienione.
         */
        if(node.has_change) {
          node.has_change = false;

          if(!(l <= this->left().l() && this->left().r() <= r)) {
            this->left().receive_change(node.latent_change);
          }
          if(!(l <= this->right().l() && this->right().r() <= r) &&
             this->right().l() < tree.elemc) {
            this->right().receive_change(node.latent_change);
          }
        }

        if(!(l > this->left().r())) {
          this->left().resum(l, r);
        }
        if(!(r < this->right().l())) {
          assert(this->right().l() < tree.elemc);
          this->right().resum(l, r);
        }
        if(this->r() < tree.elemc) {
          node.val = tree.sum(this->left().node.val, this->right().node.val);
        }
      }
    }
    void resum(size_t idx) {
      resum(idx, idx);
    }
    void resum() {
      resum(0, tree.elemc - 1);
    }
  };
};
