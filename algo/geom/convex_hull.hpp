/*
 * Otoczka wypukła - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "geom/point.hpp"
#include "geom/polygon.hpp"

/*
 * Algorytm Grahama -
 *   Znaduje otoczkę wypukłą w kolejności przeciwnej
 *   do ruchu wskazówek zegara zbioru punktów w O(n log n).
 */
template<class A>
Polygon<A> convex_hull(vector<Point<A>> pts, bool should_include_colinear = false) {
  vector<Point<A>> result;

  auto pivot = r::min(pts, SweepX());
  r::sort(pts, AngleCmp(), λ(_ - pivot));
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
