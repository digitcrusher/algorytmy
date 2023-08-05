/*
 * Najbliższa para punktów - digitcrusher/algorytmy
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
#include <functional>
#include <set>
#include <vector>

/*
 * Znajduje najbliższą parę punktów przy użyciu zamiatania w O(n log n).
 */
template<class T>
pair<Point<T>, Point<T>> closest_pair_sweep(vector<Point<T>> pts) {
  int const n = pts.size();
  assert(n >= 2);

  sort(pts.begin(), pts.end(), SweepX());
  pair result = {pts[0], pts[1]};
  auto score = (result.first - result.second).mag_sqr();

  auto consider = [&](Point<T> a, Point<T> b) {
    auto new_score = (a - b).mag_sqr();
    if(score > new_score) {
      result = {a, b};
      score = new_score;
    }
  };

  set<Point<T>, SweepY> window;
  auto tail = pts.begin();
  for(auto a: pts) {
    if(score == 0) break;
    while((a.x - tail->x) * (a.x - tail->x) >= score) {
      window.erase(*tail);
      tail++;
    }
    auto b = window.lower_bound(a);
    if(b != window.end()) {
      consider(a, *b);
    }
    if(b != window.begin()) {
      consider(a, *prev(b));
    }
    window.insert(a);
  }

  return result;
}

/*
 * Znajduje najbliższą parę punktów przy użyciu dziel i zwyciężaj w O(n log n).
 */
template<class T>
pair<Point<T>, Point<T>> closest_pair_conquer(vector<Point<T>> pts) {
  int const n = pts.size();
  assert(n >= 2);

  sort(pts.begin(), pts.end(), SweepX());
  pair result = {pts[0], pts[1]};
  auto score = (result.first - result.second).mag_sqr();

  function<void(int, int)> conquer = [&](int l, int r) {
    if(l >= r) return;

    auto mid = (l + r) / 2;
    auto mid_x = pts[mid].x;
    conquer(l, mid);
    conquer(mid + 1, r);

    inplace_merge(pts.begin() + l, pts.begin() + mid + 1, pts.begin() + r + 1, SweepY());
    for(int i = l; i <= r; i++) {
      auto a = pts[i];
      if((mid_x - a.x) * (mid_x - a.x) >= score) continue;
      for(int j = i + 1; j <= r; j++) {
        auto b = pts[j];
        if((b.y - a.y) * (b.y - a.y) >= score) break;
        auto new_score = (a - b).mag_sqr();
        if(score > new_score) {
          result = {a, b};
          score = new_score;
        }
      }
    }
  };
  conquer(0, n - 1);

  return result;
}
