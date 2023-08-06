/*
 * Convex hull trick - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "geom/point.hpp"
#include <algorithm>
#include <vector>

/*
 * Convex hull trick -
 *   Struktura wspierająca operację obliczenia maksimum albo minimum z wartości
 *   funkcji liniowych dla danego argumentu (get) w O(log n) po wstępnym
 *   przetwarzaniu w O(n log n).
 */
template<class T>
struct ConvexHullTrick {
  vector<Point<T>> hull;

  ConvexHullTrick(vector<Point<T>> funcs) {
    sort(funcs.begin(), funcs.end(), SweepX());
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

  T get(T x) {
    int left = 0, right = hull.size() - 1;
    while(left < right) {
      int mid = left + (right - left) / 2;
      // >= daje maksimum, <= - minimum
      if(dot(hull[mid + 1] - hull[mid], {x, 1}) >= 0) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return dot(hull[left], {x, 1});
  }
};
