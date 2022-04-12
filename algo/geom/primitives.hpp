/*
 * Figury geometryczne - digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include <algorithm>
#include <cmath>
#include <optional>

bool do_intersect(ld a1, ld a2, ld b1, ld b2) {
  if(a1 > a2) {
    swap(a1, a2);
  }
  if(b1 > b2) {
    swap(b1, b2);
  }
  return !(a2 < b1 || b2 < a1);
}
bool do_intersect(ld a1, ld a2, ld b) {
  if(a1 > a2) {
    swap(a1, a2);
  }
  return a1 <= b && b <= a2;
}

struct Point {
  ld x, y;

  Point() {}
  Point(ld x, ld y): x(x), y(y) {}

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
  ld dist_to(Point other) {
    return (*this - other).mag();
  }
  Point flip() {
    return {y, x};
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
bool sweep_cmp(Point a, Point b) {
  return a.x != b.x ? a.x < b.x : a.y < b.y;
}
bool angle_cmp(Point a, Point b) {
  return cross(a, b) > 0;
}
bool are_colinear(Point a, Point b, Point c) {
  return (a - c).is_colinear_with(b - c);
}

struct Segment {
  Point a, b;

  Segment() {}
  Segment(Point a, Point b): a(a), b(b) {}

  ld slope() {
    return (a.y - b.y) / (a.x - b.x);
  }
  ld intercept() {
    return cross(a, b) / (a.x - b.x);
  }
  bool is_parallel_to(Segment other) {
    return (b - a).is_colinear_with(other.b - other.a);
  }
  bool is_colinear_with(Segment other) {
    return is_parallel_to(other) && are_colinear(a, b, other.a);
  }
  enum Side {
    left, colinear, right
  };
  Side which_side(Point pt) {
    ld x = cross(b - a, pt - a);
    if(x > 0) return left;
    if(x == 0) return colinear;
    if(x < 0) return right;
    assert(false);
  }
  bool does_intersect(Segment other) {
    if(is_colinear_with(other)) {
      return do_intersect(a.x, b.x, other.a.x, other.b.x) &&
             do_intersect(a.y, b.y, other.a.y, other.b.y);
    } else {
      return which_side(other.a) != which_side(other.b) &&
             other.which_side(a) != other.which_side(b);
    }
  }
  optional<Point> intersection(Segment other) {
    Point delta_a = b - a, delta_b = other.b - other.a;
    ld x = cross(delta_a, delta_b);
    if(x == 0) {
      return nullopt;
    } else {
      ld t = cross(a - other.a, delta_b) / x;
      if(t < 0 || t > 1) {
        return nullopt;
      }
      Point result = a + delta_a * t;
      if(do_intersect(other.a.x, other.b.x, result.x) &&
         do_intersect(other.a.y, other.b.y, result.y)) {
        return nullopt;
      }
      return result;
    }
  }
};
