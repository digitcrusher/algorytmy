/*
 * Otoczka wypukła - digitcrusher/algorytmy
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
#include "geom/polygon.hpp"
#include <algorithm>
#include <vector>

/*
 * Algorytm Grahama -
 *   Znaduje otoczkę wypukłą w kolejności przeciwnej
 *   do ruchu wskazówek zegara zbioru punktów w O(n log n).
 */
template<class T>
Polygon<T> convex_hull(vector<Point<T>> pts, bool should_include_colinear = false) {
  vector<Point<T>> result;

  auto pivot = *min_element(pts.begin(), pts.end(), SweepX());
  sort(pts.begin(), pts.end(), [&](Point<T> a, Point<T> b) {
    return AngleCmp()(a - pivot, b - pivot);
  });
  if(should_include_colinear) {
    auto it = pts.end();
    while(it != pts.begin() && cross(*prev(it) - pivot, pts.back() - pivot) == 0) {
      it--;
    }
    reverse(it, pts.end());
  }
  for(auto i: pts) {
    while(result.size() >= 2) {
      auto x = cross(result.back() - result.end()[-2], i - result.back());
      if(x > 0 || (should_include_colinear && x == 0)) break;
      result.pop_back();
    }
    result.push_back(i);
  }

  return Polygon(move(result));
}
