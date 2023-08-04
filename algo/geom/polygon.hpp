/*
 * Wielokąt - digitcrusher/algorytmy
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
#include <vector>

struct Polygon {
  vector<Point> pts;

  Polygon() {}
  Polygon(vector<Point> &&pts): pts(pts) {}

  ld signed_area() {
    ld result = 0;
    auto a = pts.back();
    for(auto b: pts) {
      result += cross(a, b);
      a = b;
    }
    result /= 2;
    return result;
  }
  ld area() {
    return abs(signed_area());
  }
  bool is_ccw() {
    return signed_area() >= 0;
  }

  enum Side {
    inside, edge, outside
  };
  Side which_side(Point pt) {
    bool is_in = false;
    auto prev = pts.back();
    for(auto curr: pts) {
      auto a = prev - pt, b = curr - pt;
      if(a.y > b.y) {
        swap(a, b);
      }
      if(b.y == 0 && (b.x == 0 || (a.y == 0 && signbit(a.x) != signbit(b.x)))) {
        return edge;
      }
      if(a.y <= 0 && 0 < b.y) {
        auto x = cross(a, b);
        if(x > 0) {
          is_in = !is_in;
        } else if(x == 0) {
          return edge;
        }
      }
      prev = curr;
    }
    return is_in ? inside : outside;
  }
};
