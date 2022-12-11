/*
 * Convex hull trick - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <algorithm>
#include <vector>

struct LinFunc {
  ll a, b;

  ll operator()(ll x) {
    return a * x + b;
  }
};
LinFunc operator-(LinFunc a, LinFunc b) {
  return {a.a - b.a, a.b - b.b};
}
ll dot(LinFunc a, LinFunc b) {
  return a.a * b.a + a.b * b.b;
}
ll cross(LinFunc a, LinFunc b) {
  return a.a * b.b - a.b * b.a;
}

/*
 * Convex hull trick -
 *   Struktura wspierająca operację obliczenia maksimum albo minimum z wartości
 *   funkcji liniowych dla danego argumentu (get) w O(log n) po wstępnym
 *   przetwarzaniu w O(n log n).
 */
struct ConvexHullTrick {
  vector<LinFunc> hull;

  ConvexHullTrick(vector<LinFunc> funcs) {
    sort(funcs.begin(), funcs.end(), [](LinFunc a, LinFunc b) {
      return a.a != b.a ? a.a < b.a : a.b < b.b;
    });

    hull.reserve(funcs.size());
    for(auto func: funcs) {
      // >= daje maksimum, <= - minimum
      while(hull.size() >= 2 && cross(hull.back() - hull[hull.size() - 2],
                                      func - hull.back()) >= 0) {
        hull.pop_back();
      }
      hull.push_back(func);
    }
  }

  ll get(ll x) {
    int left = 0, right = hull.size() - 1;
    while(true) {
      int mid = left + (right - left) / 2;
      if(left >= right) {
        return hull[mid](x);
      }
      // < daje maksimum, > - minimum
      if(dot(hull[mid] - hull[mid + 1], {x, 1}) < 0) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
  }
};
