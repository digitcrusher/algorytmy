/*
 * Koło - digitcrusher/algorytmy
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

template<class A>
struct Circle {
  Point<A> center;
  A radius;

  Circle() {}
  Circle(Point<A> center, A radius): center(center), radius(radius) {}

  ld area() const {
    return numbers::pi * radius * radius;
  }

  bool does_intersect(Circle other) const {
    auto arms_length = radius + other.radius;
    return (center - other.center).mag_sqr() <= arms_length * arms_length;
  }
};
