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
#include <functional>
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
  function<bool(int, int)> dfs = [&](int node, int parent) {
    if(is_vis[node]) {
      return false;
    }
    is_vis[node] = true;
    result.push_back(node);

    for(auto neighbor: adj[node]) {
      if(neighbor == parent) continue;
      if(is_vis[neighbor]) {
        result.erase(result.begin(), find(result.begin(), result.end(), neighbor));
        return true;
      } else if(dfs(neighbor, node)) {
        return true;
      }
    }

    result.pop_back();
    return false;
  };
  for(int root = 0; root < n; root++) {
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

  vector<int> is_vis(n, 0);
  function<bool(int)> dfs = [&](int node) {
    if(is_vis[node] != 0) {
      return false;
    }
    is_vis[node] = 1;
    result.push_back(node);

    for(auto child: adj[node]) {
      if(is_vis[child] == 1) {
        result.erase(result.begin(), find(result.begin(), result.end(), child));
        return true;
      } else if(dfs(child)) {
        return true;
      }
    }

    result.pop_back();
    is_vis[node] = 2;
    return false;
  };
  for(int root = 0; root < n; root++) {
    if(dfs(root)) break;
  }

  return result.empty() ? nullopt : optional(result);
}
