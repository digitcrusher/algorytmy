/*
 * Skojarzenia w grafie - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <climits>
#include <functional>
#include <queue>
#include <vector>

/*
 * Algorytm Hopcroft-Karp (tzw. "Turbo Matching") -
 *   Znajduje największe skojarzenie w grafie dwudzielnym w O(sqrt(V) * E)
 */
struct Matching {
  vector<int> pair; // -1 jeśli dany wierzchołek nie ma pary
  int pairc;
};
Matching match_hopcroft_karp(vector<vector<int>> const& adj,
                             vector<int> const& as,
                             vector<int> const& bs)
{
  int const n = adj.size();

  vector<int> pair(n, -1);
  int pairc = 0;

  vector<int> dist(n, -1);
  auto bfs = [&]() {
    queue<int> q;
    for(int a: as) {
      if(pair[a] == -1) {
        dist[a] = 0;
        q.push(a);
      }
    }

    int max_dist = INT_MAX;
    while(!q.empty()) {
      int a = q.front();
      q.pop();

      if(dist[a] <= max_dist) {
        for(int b: adj[a]) {
          if(pair[b] == -1) {
            max_dist = dist[a];
          } else {
            if(dist[pair[b]] != -1) continue;
            dist[pair[b]] = dist[a] + 1;
            q.push(pair[b]);
          }
        }
      }
    }
    return max_dist != INT_MAX;
  };

  function<bool(int)> dfs = [&](int a) {
    int a_dist = dist[a];
    dist[a] = -1;
    for(int b: adj[a]) {
      if(pair[b] == -1 || (dist[pair[b]] == a_dist + 1 && dfs(pair[b]))) {
        pair[a] = b;
        pair[b] = a;
        return true;
      }
    }
    return false;
  };

  while(bfs()) {
    for(int a: as) {
      if(pair[a] == -1 && dfs(a)) {
        pairc++;
      }
    }
  }

  return {pair, pairc};
}
