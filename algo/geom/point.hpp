/*
 * Punkt - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <cmath>

struct Point {
  ld x, y;

  Point() {}
  Point(ld x, ld y): x(x), y(y) {}

  bool operator==(Point other) {
    return x == other.x && y == other.y;
  }
  bool operator!=(Point other) {
    return !(*this == other);
  }

  Point operator+(Point other) {
    return {x + other.x, y + other.y};
  }
  Point operator-(Point other) {
    return {x - other.x, y - other.y};
  }
  Point operator*(ld scalar) {
    return {x * scalar, y * scalar};
  }
  Point operator/(ld scalar) {
    return {x / scalar, y / scalar};
  }

  ld mag_sqr() {
    return x * x + y * y;
  }
  ld mag() {
    return hypot(y, x);
  }
  ld angle() {
    return atan2(y, x);
  }

  bool is_colinear_with(Point other);
};
// Oblicza |a| * |b| * cos θ, gdzie θ to kąt pomiędzy a i b.
ld dot(Point a, Point b) {
  return a.x * b.x + a.y * b.y;
}
// Oblicza |a| * |b| * sin θ, gdzie θ to kąt od a do b.
ld cross(Point a, Point b) {
  return a.x * b.y - a.y * b.x;
}

bool Point::is_colinear_with(Point other) {
  return cross(*this, other) == 0;
}
bool are_colinear(Point a, Point b, Point c) {
  return (a - c).is_colinear_with(b - c);
}

bool sweep_cmp(Point a, Point b) {
  return a.x != b.x ? a.x < b.x : a.y < b.y;
}
bool angle_cmp(Point a, Point b) {
  return cross(a, b) > 0;
}
