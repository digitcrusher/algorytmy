/*
 * Implicit treap - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <cstdlib>
#include <functional>
#include <ostream>
#include <vector>

/*
 * Implicit treap -
 *   Struktura danych pozwalająca na operacje podzielenia tablicy w dowolnym
 *   miejscu (split), złączenia dwóch tablic (merge), odwrócenia kolejności
 *   elementów (reverse) i obliczenia sumy przedziału elementów (get)
 *   w O(log n) po wstępnym przetwarzaniu w O(n log n).
 */
template<class Value, class Sum>
struct ImplicitTreap {
  Value val;
  int prio = rand(), elemc = 1;
  ImplicitTreap *left = nullptr, *right = nullptr;

  bool should_be_reversed = false;
  Sum sum;
  Value all_sum;

  ImplicitTreap(Value val, Sum sum = Sum()): val(val), sum(sum), all_sum(val) {}

  ~ImplicitTreap() {
    delete left;
    delete right;
  }

  static ImplicitTreap* from(vector<Value> const& elems, Sum sum = Sum()) {
    int const n = elems.size();

    vector<ImplicitTreap*> nodes(n);
    for(int i = 0; i < n; i++) {
      nodes[i] = new ImplicitTreap(elems[i], sum);
    }

    function<ImplicitTreap*(int, int)> build = [&](int l, int r) -> ImplicitTreap* {
      if(l > r) {
        return nullptr;
      }

      auto mid = l;
      for(int i = l; i <= r; i++) {
        if(nodes[mid]->prio < nodes[i]->prio) {
          mid = i;
        }
      }
      auto root = nodes[mid];
      root->left = build(l, mid - 1);
      root->right = build(mid + 1, r);
      root->children_changed();
      return root;
    };
    return build(0, n - 1);
  }

  pair<ImplicitTreap*, ImplicitTreap*> split(int idx) {
    if(idx <= 0) {
      return {nullptr, this};
    } else if(idx >= elemc) {
      return {this, nullptr};
    }

    hello();
    if(left != nullptr) {
      if(idx <= left->elemc) {
        auto [l, r] = left->split(idx);
        left = r;
        children_changed();
        return {l, this};
      } else {
        idx -= left->elemc;
      }
    }
    idx--;
    auto [l, r] = right->split(idx);
    right = l;
    children_changed();
    return {this, r};
  }

  Value get(int idx) {
    assert(0 <= idx && idx < elemc);
    hello();
    if(left != nullptr) {
      if(idx < left->elemc) {
        return left->get(idx);
      } else {
        idx -= left->elemc;
      }
    }
    if(idx == 0) {
      return val;
    }
    idx--;
    return right->get(idx);
  }

  void reverse() {
    should_be_reversed = !should_be_reversed;
  }

  Value get(int l, int r) {
    assert(0 <= l && l <= r && r < elemc);
    if(l <= 0 && elemc - 1 <= r) {
      return all_sum;
    }

    hello();
    auto mid = left != nullptr ? left->elemc : 0;
    if(r < mid) {
      return left->get(l, r);
    } else if(mid < l) {
      return right->get(l - mid - 1, r - mid - 1);
    }

    auto result = val;
    if(l < mid) {
      result = sum(left->get(l, mid - 1), result);
    }
    if(mid < r) {
      result = sum(result, right->get(0, r - mid - 1));
    }
    return result;
  }

  void hello() {
    if(should_be_reversed) {
      if(left != nullptr) {
        left->should_be_reversed = !left->should_be_reversed;
      }
      if(right != nullptr) {
        right->should_be_reversed = !right->should_be_reversed;
      }
      swap(left, right);
      should_be_reversed = false;
    }
  }
  void children_changed() {
    elemc = 1;
    all_sum = val;
    if(left != nullptr) {
      elemc += left->elemc;
      all_sum = sum(left->all_sum, all_sum);
    }
    if(right != nullptr) {
      elemc += right->elemc;
      all_sum = sum(all_sum, right->all_sum);
    }
  }
};

template<class... A>
ImplicitTreap<A...>* merge(ImplicitTreap<A...> *a, ImplicitTreap<A...> *b) {
  if(a == nullptr) {
    return b;
  } else if(b == nullptr) {
    return a;
  }

  if(a->prio >= b->prio) {
    a->hello();
    a->right = merge(a->right, b);
    a->children_changed();
    return a;
  } else {
    b->hello();
    b->left = merge(a, b->left);
    b->children_changed();
    return b;
  }
}

template<class... A>
void rotate(ImplicitTreap<A...> *&treap, int mid) {
  assert(0 <= mid && mid < treap->elemc);
  auto [a, b] = treap->split(mid);
  treap = merge(b, a);
}

template<class... A>
void reverse(ImplicitTreap<A...> *&treap, int l, int r) {
  assert(0 <= l && l <= r && r < treap->elemc);
  auto [ab, c] = treap->split(r + 1);
  auto [a, b] = ab->split(l);
  b->reverse();
  treap = merge(merge(a, b), c);
}

template<class... A>
ostream& operator<<(ostream &str, ImplicitTreap<A...> *treap) {
  treap->hello();
  if(treap->left != nullptr) {
    str << treap->left << " ";
  }
  str << treap->val;
  if(treap->right != nullptr) {
    str << " " << treap->right;
  }
  return str;
}
