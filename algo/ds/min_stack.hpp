/*
 * Stos minimum/monotoniczny - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <stack>

/*
 * Stos minimum/monotoniczny -
 *   Stos obsługujący operację obliczenia najmniejszego
 *   ze wszystkich elementów (min) w O(1).
 *
 * Cmp: (Value, Value) -> Value
 *   Zwraca true, gdy pierwszy argument jest mniejszy od drugiego.
 */
template<class Value, class Cmp>
struct MinStack {
  Cmp cmp;

  stack<pair<Value, Value>> s;

  MinStack(Cmp cmp = {}): cmp(cmp) {}

  Value top() {
    return s.top().first;
  }
  Value min() {
    return s.top().second;
  }
  void push(Value elem) {
    s.emplace(elem, s.empty() || cmp(elem, s.top().second) ? elem : s.top().second);
  }
  void pop() {
    s.pop();
  }
  void clear() {
    decltype(s)().swap(s);
  }
  bool empty() {
    return s.empty();
  }
  int size() {
    return s.size();
  }
};
