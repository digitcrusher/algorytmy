/*
 * Odcinek - digitcrusher/algorytmy
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
#include <optional>
#include <utility>

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

  bool is_parallel_to(Segment other) {
    return (b - a).is_colinear_with(other.b - other.a);
  }
  bool is_colinear_with(Segment other) {
    return is_parallel_to(other) && are_colinear(a, b, other.a);
  }

  static bool do_intersect(ld a1, ld a2, ld b1, ld b2) {
    if(a1 > a2) {
      swap(a1, a2);
    }
    if(b1 > b2) {
      swap(b1, b2);
    }
    return !(a2 < b1 || b2 < a1);
  }
  static bool do_intersect(ld a1, ld a2, ld b) {
    if(a1 > a2) {
      swap(a1, a2);
    }
    return a1 <= b && b <= a2;
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
  bool does_intersect(Point pt) {
    return which_side(pt) == colinear &&
           do_intersect(a.x, b.x, pt.x) &&
           do_intersect(a.y, b.y, pt.y);
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
