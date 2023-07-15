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
#include <functional>
#include <optional>
#include <vector>

/*
 * Dwukolorowanie grafu nieskierowanego -
 *   Przypisuje każdemu wierzchołkowi liczbę 1 albo 2 w O(V + E)
 *   tak, aby dwie takie same liczby nie sąsiadowały ze sobą.
 */
optional<vector<int>> two_color(vector<vector<int>> const& adj) {
  int const n = adj.size();

  vector<int> color(n, -1);
  function<bool(int)> assign = [&](int node) {
    for(auto neighbor: adj[node]) {
      if(color[neighbor] == -1) {
        color[neighbor] = color[node] == 1 ? 2 : 1;
        if(!assign(neighbor)) {
          return false;
        }
      } else if(color[neighbor] == color[node]) {
        return false;
      }
    }
    return true;
  };

  for(int root = 0; root < n; root++) {
    if(color[root] != -1) continue;
    color[root] = 1;
    if(!assign(root)) {
      return nullopt;
    }
  }

  return color;
}
