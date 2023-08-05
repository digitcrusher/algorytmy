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

template<class T>
struct Point {
  T x, y;

  Point() {}
  Point(T x, T y): x(x), y(y) {}
  template<class U>
  Point(Point<U> other): x(other.x), y(other.y) {}

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
  Point operator*(T scalar) {
    return {x * scalar, y * scalar};
  }
  Point operator/(T scalar) {
    return {x / scalar, y / scalar};
  }

  T mag_sqr() {
    return x * x + y * y;
  }
  ld mag() {
    return hypotl(y, x);
  }
  ld angle() {
    return atan2l(y, x);
  }

  bool is_colinear_with(Point other);
};

// Oblicza |a| * |b| * cos θ, gdzie θ to kąt pomiędzy a i b.
template<class T>
T dot(Point<T> a, Point<T> b) {
  return a.x * b.x + a.y * b.y;
}
// Oblicza |a| * |b| * sin θ, gdzie θ to kąt od a do b.
template<class T>
T cross(Point<T> a, Point<T> b) {
  return a.x * b.y - a.y * b.x;
}

template<class T>
bool Point<T>::is_colinear_with(Point other) {
  return cross(*this, other) == 0;
}
template<class T>
bool are_colinear(Point<T> a, Point<T> b, Point<T> c) {
  return (a - c).is_colinear_with(b - c);
}

struct SweepX {
  template<class T>
  bool operator()(Point<T> a, Point<T> b) const {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
  }
};
struct SweepY {
  template<class T>
  bool operator()(Point<T> a, Point<T> b) const {
    return a.y != b.y ? a.y < b.y : a.x < b.x;
  }
};

struct AngleCmp {
  template<class T>
  bool operator()(Point<T> a, Point<T> b) const {
    auto x = cross(a, b);
    return x != 0 ? x > 0 : a.mag_sqr() < b.mag_sqr();
  }
};
