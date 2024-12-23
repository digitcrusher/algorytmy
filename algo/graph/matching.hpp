/*
 * Skojarzenie - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <queue>

/*
 * Algorytm Hopcroft-Karp (tzw. "Turbo Matching") -
 *   Znajduje największe skojarzenie w grafie dwudzielnym w O(sqrt(V) * E).
 */
struct Matching {
  vector<int> pair; // -1 jeśli dany wierzchołek nie ma pary
  int pairc;
};
Matching match_hopcroft_karp(vector<vector<int>> const& adj,
                             vector<int> const& as,
                             vector<int> const& bs)
{
  int n = adj.size();

  vector pair(n, -1);
  auto pairc = 0;

  vector<int> dist(n);
  auto bfs = [&]() {
    queue<int> q;
    for(auto a: as) {
      if(pair[a] == -1) {
        dist[a] = 0;
        q.push(a);
      } else {
        dist[a] = -1;
      }
    }

    int max_dist = INT_MAX;
    while(!q.empty()) {
      auto a = q.front();
      q.pop();

      if(dist[a] >= max_dist) continue;

      for(auto b: adj[a]) {
        if(pair[b] == -1) {
          max_dist = dist[a];
        } else if(dist[pair[b]] == -1) {
          dist[pair[b]] = dist[a] + 1;
          q.push(pair[b]);
        }
      }
    }
    return max_dist != INT_MAX;
  };

  auto dfs = Y([&](auto &self, int a) -> bool {
    for(auto b: adj[a]) {
      if(pair[b] == -1 || (dist[pair[b]] == dist[a] + 1 && self(pair[b]))) {
        pair[a] = b;
        pair[b] = a;
        return true;
      }
    }
    dist[a] = -1;
    return false;
  });

  while(bfs()) {
    for(auto a: as) {
      if(pair[a] == -1 && dfs(a)) {
        pairc++;
      }
    }
  }

  return {pair, pairc};
}
