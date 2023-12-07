/*
 * Kolejka minimum/monotoniczna - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "ds/min_stack.hpp"
#include <deque>

/*
 * Leniwa kolejka minimum/monotoniczna -
 *   Kolejka obsługująca operację obliczenia najmniejszego ze wszystkich
 *   elementów (min) w O(1), ale bez operacji zwrócenia pierwszego elementu.
 *
 * Cmp: (Value, Value) -> Value
 *   Zwraca true, gdy pierwszy argument jest mniejszy od drugiego.
 */
template<class Value, class Cmp>
struct LazyMinQueue {
  Cmp cmp;

  deque<pair<Value, int>> q;
  int pushc = 0, popc = 0;

  LazyMinQueue(Cmp cmp = {}): cmp(cmp) {}

  Value min() {
    return q.front().first;
  }
  void push(Value elem) {
    while(!q.empty() && !cmp(q.back().first, elem)) {
      q.pop_back();
    }
    q.emplace_back(elem, pushc);
    pushc++;
  }
  void pop() {
    if(q.front().second == popc) {
      q.pop_front();
    }
    popc++;
  }
  void clear() {
    q.clear();
    pushc = 0;
    popc = 0;
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

  MinQueue(Cmp cmp = {}): cmp(cmp), in(cmp), out(cmp) {}

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
  void clear() {
    in.clear();
    out.clear();
  }
  bool empty() {
    return in.empty() && out.empty();
  }
  int size() {
    return in.size() + out.size();
  }
};
