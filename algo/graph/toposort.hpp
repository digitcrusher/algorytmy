/*
 * Sortowanie topologiczne - digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include <queue>
#include <stdexcept>
#include <vector>

/*
 * Algorytm Kahn'a -
 *   Znajduje dowolne sortowanie topologiczne
 *   skierowanego grafu acyklicznego w O(V + E).
 */
vector<int> toposort_kahn(vector<vector<int>> const& adj, vector<int> in_deg) {
  int const n = adj.size();

  vector<int> result;
  result.reserve(n);

  /*
    * Po zamianie queue na priority_queue z komparatorem greater<int>,
    * ten algorytm zwracałby najmniejsze leksykograficznie sortowanie
    * topologiczne w czasie O(V log V + E).
    */
  queue<int> q;
  for(int root = 0; root < n; root++) {
    if(in_deg[root] == 0) {
      q.push(root);
    }
  }
  while(!q.empty()) {
    int node = q.front();
    q.pop();

    result.push_back(node);

    for(int child: adj[node]) {
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
