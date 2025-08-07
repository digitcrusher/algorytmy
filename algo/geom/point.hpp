/*
 * Punkt - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "hash.hpp"
#include <cmath>
#include <iostream>

template<class A>
struct Point {
  A x, y;

  Point() {}
  Point(A x, A y): x(x), y(y) {}
  template<class B>
  Point(Point<B> other): x(other.x), y(other.y) {}

  bool operator==(Point other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(Point other) const {
    return !(*this == other);
  }
  Point operator+(Point other) const {
    return {x + other.x, y + other.y};
  }
  Point operator-(Point other) const {
    return {x - other.x, y - other.y};
  }
  Point operator*(Point other) const {
    return {x * other.x - y * other.y, x * other.y + y * other.x};
  }
  Point operator*(A scalar) const {
    return {x * scalar, y * scalar};
  }
  Point operator/(A scalar) const {
    return {x / scalar, y / scalar};
  }
  Point& operator+=(Point other) {
    return *this = *this + other;
  }
  Point& operator-=(Point other) {
    return *this = *this - other;
  }
  Point& operator*=(Point other) {
    return *this = *this * other;
  }
  Point& operator*=(A scalar) {
    return *this = *this * scalar;
  }
  Point& operator/=(A scalar) {
    return *this = *this / scalar;
  }

  A mag_sqr() const {
    return x * x + y * y;
  }
  ld mag() const {
    return hypotl(x, y);
  }
  ld angle() const {
    return atan2l(y, x);
  }
  A gcd() const {
    return ::gcd(x, y);
  }
  Point unit() const {
    return {x / mag(), y / mag()};
  }
  Point rot90() const {
    return {-y, x};
  }
  Point rot270() const {
    return {y, -x};
  }
  Point conj() const {
    return {x, -y};
  }

  bool is_colinear_with(Point other) const;
};

// Oblicza |a| * |b| * cos θ, gdzie θ to kąt pomiędzy a i b.
template<class A>
A dot(Point<A> a, Point<A> b) {
  return a.x * b.x + a.y * b.y;
}
// Oblicza |a| * |b| * sin θ, gdzie θ to kąt od a do b.
template<class A>
A cross(Point<A> a, Point<A> b) {
  return a.x * b.y - a.y * b.x;
}

template<class A>
bool Point<A>::is_colinear_with(Point other) const {
  return cross(*this, other) == 0;
}
template<class A>
bool are_colinear(Point<A> a, Point<A> b, Point<A> c) {
  return (a - c).is_colinear_with(b - c);
}

struct SweepX {
  template<class A>
  bool operator()(Point<A> a, Point<A> b) const {
    return tie(a.x, a.y) < tie(b.x, b.y);
  }
};
struct SweepY {
  template<class A>
  bool operator()(Point<A> a, Point<A> b) const {
    return tie(a.y, a.x) < tie(b.y, b.x);
  }
};

struct AngleCmp {
  template<class A>
  bool operator()(Point<A> a, Point<A> b) const {
    auto half_a = a.y < 0 || (a.y == 0 && a.x < 0),
         half_b = b.y < 0 || (b.y == 0 && b.x < 0);
    if(half_a != half_b) {
      return half_a < half_b;
    }
    auto x = cross(a, b);
    return x != 0 ? x > 0 : a.mag_sqr() < b.mag_sqr();
  }
};

ostream& operator<<(ostream &stream, Point<auto> pt) {
  return stream << pt.x << " " << pt.y;
}
istream& operator>>(istream &stream, Point<auto> &pt) {
  return stream >> pt.x >> pt.y;
}
template<class A>
struct std::hash<Point<A>> {
  size_t operator()(Point<A> pt) const {
    return hash_many<A, A>()(pt.x, pt.y);
  }
};
