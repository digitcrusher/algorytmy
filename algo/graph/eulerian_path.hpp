/*
 * Ścieżka Eulera (lub cykl) - digitcrusher/algorytmy
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
#include <unordered_set>

/*
 * Znajduje ścieżkę Eulera (lub cykl) w grafie skierowanym w O(V + E).
 */
optional<vector<int>> eulerian_path_dir(vector<vector<int>> adj) {
  int n = adj.size();

  auto m = 0;
  vector deg(n, 0);
  for(auto a: v::iota(0, n)) {
    m += adj[a].size();
    deg[a] += adj[a].size();
    for(auto b: adj[a]) {
      deg[b]--;
    }
  }
  auto start = -1, end = -1;
  for(auto i: v::iota(0, n)) {
    if(deg[i] == 1 && start == -1) {
      start = i;
    } else if(deg[i] == -1 && end == -1) {
      end = i;
    } else if(deg[i] != 0) {
      return nullopt;
    }
  }
  if(start == -1) {
    start = end = 0;
  }

  vector<int> result(m + 1);
  auto next_idx = m;

  auto walk = Y([&](auto &self, int node) -> void {
    while(!adj[node].empty()) {
      auto child = adj[node].back();
      adj[node].pop_back();
      self(child);
    }
    result[next_idx] = node;
    next_idx--;
  });
  walk(start);

  return next_idx < 0 ? optional(result) : nullopt;
}

/*
 * Znajduje ścieżkę Eulera (lub cykl) w grafie nieskierowanym w O(V + E).
 */
optional<vector<int>> eulerian_path_undir(vector<vector<int>> adj) {
  int n = adj.size();

  auto m = 0, start = -1, end = -1;
  for(auto i: v::iota(0, n)) {
    m += adj[i].size();
    if(adj[i].size() % 2 == 0) continue;
    if(start == -1) {
      start = i;
    } else if(end == -1) {
      end = i;
    } else {
      return nullopt;
    }
  }
  m /= 2;
  if(start == -1) {
    start = end = 0;
  }

  vector<int> result;
  result.reserve(m + 1);

  unordered_multiset<pair<int, int>> used_edges;
  auto walk = Y([&](auto &self, int node) -> void {
    while(!adj[node].empty()) {
      auto neighbor = adj[node].back();
      adj[node].pop_back();
      auto it = used_edges.find({neighbor, node});
      if(it == used_edges.end()) {
        used_edges.insert({node, neighbor});
        self(neighbor);
      } else {
        used_edges.erase(it);
      }
    }
    result.push_back(node);
  });
  walk(end);

  return result.size() == m + 1 ? optional(result) : nullopt;
}
