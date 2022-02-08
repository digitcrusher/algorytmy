/*
 * Stos i kolejka minimum/monotoniczna - digitcrusher/algorytmy
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

  bool empty() {
    return s.empty();
  }
  int size() {
    return s.size();
  }
};

/*
 * Leniwa kolejka minimum/monotoniczna -
 *   Kolejka obsługująca operację obliczenia najmniejszego ze wszystkich
 *   elementów (min) w O(1), ale bez operacji zwrócenia pierwszego elementu
 *   (front).
 *
 * Cmp: (Value, Value) -> Value
 *   Zwraca true, gdy pierwszy argument jest mniejszy od drugiego.
 */
template<class Value, class Cmp>
struct LazyMinQueue {
  Cmp cmp;

  deque<pair<Value, int>> q;
  int pushc = 0, popc = 0;

  LazyMinQueue(Cmp cmp = Cmp()): cmp(cmp) {}

  Value min() {
    return q.top().first;
  }
  void push(Value elem) {
    while(!q.empty() && !cmp(q.back().first, elem)) {
      q.pop_back();
    }
    q.push_back({elem, pushc});
    pushc++;
  }
  void pop() {
    if(q.front().second == popc) {
      q.pop_front();
    }
    popc++;
  }

  bool empty() {
    return q.empty();
  }
  int size() {
    return pushc - popc;
  }
};

/*
 * Kolejka minimum/monotoniczna -
 *   Kolejka obsługująca operację obliczenia najmniejszego
 *   ze wszystkich elementów (min) w O(1).
 *
 * Cmp: (Value, Value) -> Value
 *   Zwraca true, gdy pierwszy argument jest mniejszy od drugiego.
 */
template<class Value, class Cmp>
struct MinQueue {
  Cmp cmp;

  MinStack<Value, Cmp> in, out;

  MinQueue(Cmp cmp = Cmp()): cmp(cmp), in(cmp), out(cmp) {}

  Value front() {
    if(out.empty()) {
      while(!in.empty()) {
        out.push(in.top());
        in.pop();
      }
    }
    return out.top();
  }
  Value min() {
    if(out.empty() || (!in.empty() && cmp(in.min(), out.min()))) {
      return in.min();
    } else {
      return out.min();
    }
  }
  void push(Value elem) {
    in.push(elem);
  }
  void pop() {
    if(out.empty()) {
      while(!in.empty()) {
        out.push(in.top());
        in.pop();
      }
    }
    out.pop();
  }

  bool empty() {
    return in.empty() && out.empty();
  }
  int size() {
    return in.size() + out.size();
  }
};
