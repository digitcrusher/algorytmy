/*
 * Maksymalny przeplyw - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <climits>
#include <queue>
#include <vector>

/*
 * Algorytm Edmondsa-Karpa -
 *   Znajduje maksymalny przepływ w grafie skierowanym w czasie O(V * E^2).
 *   Jeden ze zbiorów minimalnego przecięcia można znaleźć za pomocą DFSa po
 *   nienasyconych krawędziach puszczonego ze źródła lub ujścia.
 */
struct MaxFlow {
  vector<vector<ll>> flow;
  ll global_flow;
};
MaxFlow max_flow(vector<vector<pair<int, ll>>> const& adj, int src, int sink) {
  int const n = adj.size();

  vector flow(n, vector(n, 0ll));
  ll global_flow = 0;

  vector<vector<int>> undir_adj(n);
  vector cap(n, vector(n, 0ll));
  for(auto a: v::iota(0, n)) {
    for(auto [b, edge_cap]: adj[a]) {
      undir_adj[a].push_back(b);
      undir_adj[b].push_back(a);
      cap[a][b] += edge_cap;
    }
  }

  while(true) {
    vector path_cap(n, 0ll);
    vector prev(n, -1);
    queue<int> q;

    path_cap[src] = LLONG_MAX;
    q.push(src);

    while(!q.empty()) {
      auto node = q.front();
      q.pop();

      for(auto neighbor: undir_adj[node]) {
        auto new_cap = min(path_cap[node], cap[node][neighbor]);
        if(path_cap[neighbor] < new_cap) {
          path_cap[neighbor] = new_cap;
          if(prev[neighbor] == -1) {
            q.push(neighbor);
          }
          prev[neighbor] = node;
        }
      }
    }

    auto new_flow = path_cap[sink];
    if(new_flow == 0) break;
    global_flow += new_flow;

    for(auto node = sink; node != src; node = prev[node]) {
      cap[prev[node]][node] -= new_flow;
      cap[node][prev[node]] += new_flow;
      flow[prev[node]][node] += new_flow;
      flow[node][prev[node]] -= new_flow;
    }
  }

  return {flow, global_flow};
}
