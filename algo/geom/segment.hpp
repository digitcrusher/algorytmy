/*
 * Odcinek - digitcrusher/algorytmy
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
#include "math/int.hpp"
#include <iostream>

template<class A>
struct Segment {
  Point<A> a, b;

  Segment() {}
  Segment(Point<A> a, Point<A> b): a(a), b(b) {}

  ld slope() const {
    return (a.y - b.y) / (ld) (a.x - b.x);
  }
  ld intercept() const {
    return cross(a, b) / (ld) (a.x - b.x);
  }

  enum Side {
    left, colinear, right
  };
  Side which_side(Point<A> pt) const {
    auto x = cross(b - a, pt - a);
    if(x > 0) return left;
    if(x == 0) return colinear;
    if(x < 0) return right;
    assert(false);
  }

  bool is_parallel_to(Segment other) const {
    return (b - a).is_colinear_with(other.b - other.a);
  }
  bool is_colinear_with(Segment other) const {
    return is_parallel_to(other) && are_colinear(a, b, other.a);
  }

  bool does_intersect(Segment other) const {
    if(is_colinear_with(other)) {
      return do_intersect(a.x, b.x, other.a.x, other.b.x) &&
             do_intersect(a.y, b.y, other.a.y, other.b.y);
    } else {
      return which_side(other.a) != which_side(other.b) &&
             other.which_side(a) != other.which_side(b);
    }
  }
  bool does_intersect(Point<A> pt) const {
    return which_side(pt) == colinear &&
           do_intersect(a.x, b.x, pt.x) &&
           do_intersect(a.y, b.y, pt.y);
  }

  optional<Point<ld>> intersection(Segment other) const {
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

ostream& operator<<(ostream &stream, Segment<auto> seg) {
  return stream << seg.a << " " << seg.b;
}
istream& operator>>(istream &stream, Segment<auto> &seg) {
  return stream >> seg.a >> seg.b;
}
