/*
 * Twierdzenia Picka - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "geom/polygon.hpp"
#include <numeric>

/*
 * Na podstawie tw. Picka oblicza liczbę punktów kratowych zawartych
 * w wielokącie, którego wierzchołki leżą na punktach kratowych.
 */
struct Pick {
  ll insidec, on_edgec;
};
Pick pick(Polygon<ll> const& poly, ll doubled_area) {
  ll on_edgec = 0;
  auto a = poly.pts.back();
  for(auto b: poly.pts) {
    on_edgec += gcd(a.x - b.x, a.y - b.y);
    a = b;
  }
  auto insidec = (doubled_area - on_edgec) / 2 + 1;
  return {insidec, on_edgec};
}
