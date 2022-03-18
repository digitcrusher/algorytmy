/*
 * Mosty i punkty artykulacji - digitcrusher/algorytmy
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
#include <functional>
#include <vector>

/*
 * Znajduje mosty i punkty artykulacji w grafie
 * nieskierowanym bez krawędzi wielokrotnych w O(V + E).
 */
struct Bridges {
  vector<pair<int, int>> bridges;
  vector<int> cut_vertices;
};
Bridges bridges(vector<vector<int>> const& adj) {
  int const n = adj.size();

  vector<pair<int, int>> bridges;
  vector<int> cut_vertices;

  vector<int> entry(n, -1), low(n);
  function<int(int, int)> dfs = [&](int node, int parent) {
    bool is_cut = false;
    int subgraphc = 0;

    low[node] = entry[node];
    int post = entry[node] + 1;
    for(int child: adj[node]) {
      if(child == parent) continue;
      if(entry[child] == -1) {
        entry[child] = post;
        post = dfs(child, node);
        low[node] = min(low[node], low[child]);

        if(entry[node] < low[child]) {
          bridges.push_back({node, child});
        }
        if(entry[node] == 0) {
          subgraphc++;
        } else {
          is_cut |= entry[node] <= low[child];
        }
      } else {
        low[node] = min(low[node], entry[child]);
      }
    }

    if(entry[node] == 0) {
      is_cut = subgraphc > 1;
    }
    if(is_cut) {
      cut_vertices.push_back(node);
    }
    return post;
  };

  for(int root = 0; root < n; root++) {
    if(entry[root] != -1) continue;
    entry[root] = 0;
    dfs(root, -1);
  }

  return {bridges, cut_vertices};
}
