/*
 * Koło - digitcrusher/algorytmy
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
#include <numbers>

template<class A>
struct Circle {
  Point<A> center;
  A radius;

  Circle() {}
  Circle(Point<A> center, A radius): center(center), radius(radius) {}

  ld area() {
    return numbers::pi * radius * radius;
  }

  bool does_intersect(Circle other) {
    auto arms_length = radius + other.radius;
    return (center - other.center).mag_sqr() <= arms_length * arms_length;
  }
};
