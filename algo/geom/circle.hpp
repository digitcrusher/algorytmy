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
#include "misc.hpp"

struct Circle {
  Point center;
  ld radius;

  Circle() {}
  Circle(Point center, ld radius): center(center), radius(radius) {}

  ld area() {
    return pi * radius * radius;
  }

  bool does_intersect(Circle other) {
    auto arms_length = radius + other.radius;
    return (center - other.center).mag_sqr() <= arms_length * arms_length;
  }
};
