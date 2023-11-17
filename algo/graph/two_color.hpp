/*
 * Dwukolorowanie grafu - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <optional>
#include <vector>

/*
 * Dwukolorowanie grafu nieskierowanego -
 *   Przypisuje każdemu wierzchołkowi liczbę 1 albo 2 w O(V + E)
 *   tak, aby dwie takie same liczby nie sąsiadowały ze sobą.
 */
optional<vector<int>> two_color(vector<vector<int>> const& adj) {
  int const n = adj.size();

  vector color(n, -1);
  auto assign = Y([&](auto &self, int node) -> bool {
    for(auto neighbor: adj[node]) {
      if(color[neighbor] == -1) {
        color[neighbor] = color[node] == 1 ? 2 : 1;
        if(!self(neighbor)) {
          return false;
        }
      } else if(color[neighbor] == color[node]) {
        return false;
      }
    }
    return true;
  });

  for(auto root: v::iota(0, n) | v::filter(λ(color[_] == -1))) {
    color[root] = 1;
    if(!assign(root)) {
      return nullopt;
    }
  }

  return color;
}
