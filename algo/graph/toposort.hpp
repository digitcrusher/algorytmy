/*
 * Sortowanie topologiczne - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <queue>

/*
 * Algorytm Kahna -
 *   Znajduje dowolne sortowanie topologiczne
 *   skierowanego grafu acyklicznego w O(V + E).
 */
vector<int> toposort_kahn(vector<vector<int>> const& adj, vector<int> in_deg) {
  int n = adj.size();

  vector<int> result;
  result.reserve(n);

  /*
   * Poniższy BFS może być równie dobrze zastąpiony DFSem.
   *
   * Po zamianie queue na priority_queue z komparatorem greater<>,
   * ten algorytm zwracałby najmniejsze leksykograficznie sortowanie
   * topologiczne w czasie O(V log V + E).
   */
  queue<int> q;
  for(auto root: v::iota(0, n) | v::filter(λ(in_deg[_] == 0))) {
    q.push(root);
  }
  while(!q.empty()) {
    auto node = q.front();
    q.pop();

    result.push_back(node);

    for(auto child: adj[node]) {
      in_deg[child]--;
      if(in_deg[child] == 0) {
        q.push(child);
      }
    }
  }

  if(result.size() != n) {
    throw std::runtime_error("Graf nie jest acykliczny.");
  }
  return result;
}

/*
 * Znajduje dowolne sortowanie topologiczne skierowanego
 * grafu acyklicznego z użyciem DFS w O(V + E).
 */
vector<int> toposort_dfs(vector<vector<int>> const& adj) {
  int n = adj.size();

  vector<int> result(n);
  auto next_idx = n - 1;

  vector is_vis(n, 0);
  auto dfs = Y([&](auto &self, int node) -> void {
    if(is_vis[node] == 2) return;
    if(is_vis[node] == 1) {
      throw std::runtime_error("Graf nie jest acykliczny.");
    }
    is_vis[node] = 1;

    for(auto child: adj[node]) {
      self(child);
    }
    result[next_idx] = node;
    next_idx--;

    is_vis[node] = 2;
  });
  for(auto root: v::iota(0, n)) {
    dfs(root);
  }

  return result;
}
