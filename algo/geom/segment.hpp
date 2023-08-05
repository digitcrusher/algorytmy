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

template<class T>
struct Segment {
  Point<T> a, b;

  Segment() {}
  Segment(Point<T> a, Point<T> b): a(a), b(b) {}

  ld slope() {
    return (ld) (a.y - b.y) / (a.x - b.x);
  }
  ld intercept() {
    return (ld) cross(a, b) / (a.x - b.x);
  }

  enum Side {
    left, colinear, right
  };
  Side which_side(Point<T> pt) {
    auto x = cross(b - a, pt - a);
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

  template<class U>
  bool do_intersect(U a1, U a2, U b1, U b2) {
    if(a1 > a2) {
      swap(a1, a2);
    }
    if(b1 > b2) {
      swap(b1, b2);
    }
    return !(a2 < b1 || b2 < a1);
  }
  template<class U>
  bool do_intersect(U a1, U a2, U b) {
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
  bool does_intersect(Point<T> pt) {
    return which_side(pt) == colinear &&
           do_intersect(a.x, b.x, pt.x) &&
           do_intersect(a.y, b.y, pt.y);
  }

  optional<Point<ld>> intersection(Segment other) {
    ld x = cross(b - a, other.b - other.a);
    if(x == 0) {
      return nullopt;
    } else {
      auto on_me = cross(other.b - other.a, a - other.a) / x;
      if(on_me < 0 || on_me > 1) {
        return nullopt;
      }
      return Point<ld>(a) + Point<ld>(b - a) * on_me;
    }
  }
};
