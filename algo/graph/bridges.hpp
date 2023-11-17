/*
 * Mosty, punkty artykulacji i dwuspójne składowe - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <vector>

/*
 * Znajduje mosty, punkty artykulacji i dwuspójne składowe
 * w grafie nieskierowanym bez krawędzi wielokrotnych w O(V + E).
 */
struct Bridges {
  vector<pair<int, int>> bridges;
  vector<int> cut_vertices;
};
struct BCCs {
  vector<int> parent;
  /*
   * Tylko reprezentanci (najniższe wierzchołki)
   * dwuspójnych składowych trzymają krawędzie między nimi.
   */
  vector<vector<int>> adj;

  int find_bcc(int node) {
    return parent[node] == node ? node : parent[node] = find_bcc(parent[node]);
  }
};
pair<Bridges, BCCs> bridges(vector<vector<int>> const& adj) {
  int const n = adj.size();

  vector<pair<int, int>> bridges;
  vector<int> cut_vertices;

  BCCs bccs;
  bccs.parent.resize(n);
  bccs.adj.resize(n);

  vector<int> entry(n, -1), low(n);
  auto dfs = Y([&](auto &self, int node, int parent) -> int {
    auto is_cut = false;
    bccs.parent[node] = node;

    low[node] = entry[node];
    auto exit = entry[node];
    auto is_first_child = true;
    for(auto child: adj[node] | v::filter(λ(_ != parent))) {
      if(entry[child] == -1) {
        entry[child] = exit + 1;
        exit = self(child, node);
        low[node] = min(low[node], low[child]);

        if(entry[node] < low[child]) {
          bridges.emplace_back(node, child);
        }
        if(parent == -1) {
          is_cut |= !is_first_child;
        } else {
          is_cut |= entry[node] <= low[child];
        }
        is_first_child = false;

        if(entry[bccs.parent[child]] < entry[bccs.parent[node]]) {
          bccs.parent[node] = bccs.parent[child];
        }
      } else {
        low[node] = min(low[node], entry[child]);

        if(entry[child] < entry[bccs.parent[node]]) {
          bccs.parent[node] = child;
        }
      }
    }

    if(is_cut) {
      cut_vertices.push_back(node);
    }
    return exit;
  });

  vector is_vis(n, false);
  auto connect_bccs = Y([&](auto &self, int node) -> int {
    is_vis[node] = true;
    auto a = bccs.find_bcc(node);
    for(auto child: adj[node] | v::filter(λ(!is_vis[_]))) {
      auto b = self(child);
      if(a == b) continue;
      bccs.adj[a].push_back(b);
      bccs.adj[b].push_back(a);
    }
    return a;
  });

  for(auto root: v::iota(0, n) | v::filter(λ(entry[_] == -1))) {
    entry[root] = 0;
    dfs(root, -1);
    connect_bccs(root);
  }

  return {{bridges, cut_vertices}, bccs};
}
