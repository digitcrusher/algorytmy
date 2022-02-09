/*
 * Stos minimum/monotoniczna - digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include <stack>

/*
 * Stos minimum/monotoniczny -
 *   Stos obsługujący operację obliczenia najmniejszego ze
 *   wszystkich elementów (min) w O(1). Zużywa O(n) pamięci.
 *
 * Cmp: (Value, Value) -> Value
 *   Zwraca true, gdy pierwszy argument jest mniejszy od drugiego.
 */
template<class Value, class Cmp>
struct MinStack {
  Cmp cmp;

  stack<pair<Value, Value>> s;

  MinStack(Cmp cmp = Cmp()): cmp(cmp) {}

  Value top() {
    return s.top().first;
  }
  Value min() {
    return s.top().second;
  }
  void push(Value elem) {
    s.push({elem, s.empty() || cmp(elem, s.top().second) ? elem : s.top().second});
  }
  void pop() {
    s.pop();
  }
  void clear() {
    s.clear();
  }
  bool empty() {
    return s.empty();
  }
  int size() {
    return s.size();
  }
};
