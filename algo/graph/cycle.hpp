/*
 * Cykle - digitcrusher/algorytmy
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
 * Znajduje dowolny cykl w grafie nieskierowanym w O(V + E).
 */
optional<vector<int>> find_cycle_undir(vector<vector<int>> const& adj) {
  int const n = adj.size();

  vector<int> result;
  result.reserve(n);

  vector is_vis(n, false);
  auto dfs = Y([&](auto &self, int node, int parent) -> bool {
    if(is_vis[node]) {
      return false;
    }
    is_vis[node] = true;
    result.push_back(node);

    for(auto neighbor: adj[node] | v::filter(λ(_ != parent))) {
      if(is_vis[neighbor]) {
        result.erase(result.begin(), r::find(result, neighbor));
        return true;
      } else if(self(neighbor, node)) {
        return true;
      }
    }

    result.pop_back();
    return false;
  });
  for(auto root: v::iota(0, n)) {
    if(dfs(root, -1)) break;
  }

  return result.empty() ? nullopt : optional(result);
}

/*
 * Znajduje dowolny cykl w grafie skierowanym w O(V + E).
 */
optional<vector<int>> find_cycle_dir(vector<vector<int>> const& adj) {
  int const n = adj.size();

  vector<int> result;
  result.reserve(n);

  vector is_vis(n, 0);
  auto dfs = Y([&](auto &self, int node) -> bool {
    if(is_vis[node] != 0) {
      return false;
    }
    is_vis[node] = 1;
    result.push_back(node);

    for(auto child: adj[node]) {
      if(is_vis[child] == 1) {
        result.erase(result.begin(), r::find(result, child));
        return true;
      } else if(self(child)) {
        return true;
      }
    }

    result.pop_back();
    is_vis[node] = 2;
    return false;
  });
  for(auto root: v::iota(0, n)) {
    if(dfs(root)) break;
  }

  return result.empty() ? nullopt : optional(result);
}
