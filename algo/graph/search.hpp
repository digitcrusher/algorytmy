/*
 * Przeszukiwanie grafu - digitcrusher/algorytmy
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
 * Breadth-first search (BFS) -
 *   Podstawowy budulec wielu algorytmów grafowych. Przeszukuje graf wszerz
 *   w O(V + E) tworząc z odwiedzonych wierzchołków drzewo rozpinające
 *   ukorzenione w wierzchołku root. Ta implementacja jest tylko w celach
 *   demonstracyjnych.
 */
struct BFS {
  vector<bool> is_vis;
  vector<int> parent, dist;
};
BFS bfs(vector<vector<int>> const& adj, int root) {
  int n = adj.size();

  vector is_vis(n, false);
  vector<int> parent(n), dist(n);

  queue<int> q;
  is_vis[root] = true;
  parent[root] = -1;
  dist[root] = 0;
  q.push(root);
  while(!q.empty()) {
    auto node = q.front();
    q.pop();

    for(auto child: adj[node] | v::filter(λ(!is_vis[_]))) {
      is_vis[child] = true;
      parent[child] = node;
      dist[child] = dist[node] + 1;
      q.push(child);
    }
  }

  return {is_vis, parent, dist};
}

/*
 * Depth-first search (DFS) -
 *   Podstawowy budulec wielu algorytmów grafowych. Przeszukuje graf w głąb
 *   w O(V + E) tworząc z odwiedzonych wierzchołków drzewo rozpinające
 *   ukorzenione w wierzchołku root (tzw. drzewo DFS). Takie drzewo nie
 *   ma krawędzi poprzecznych. Ta implementacja jest tylko w celach
 *   demonstracyjnych.
 */
struct DFS {
  vector<bool> is_vis;
  vector<int> parent, depth, size;
  vector<int> entry, exit, low;
  vector<int> pre_order, post_order;
};
DFS dfs(vector<vector<int>> const& adj, int root) {
  int n = adj.size();

  vector is_vis(n, false);
  vector<int> parent(n), depth(n), size(n);
  vector<int> entry(n), exit(n), low(n);
  vector<int> pre_order, post_order;
  pre_order.reserve(n);
  post_order.reserve(n);

  auto walk = Y([&](auto &self, int node) -> void {
    size[node] = 1;
    exit[node] = entry[node] + 1;
    low[node] = entry[node];
    pre_order.push_back(node);

    for(auto child: adj[node] | v::filter(λ(_ != parent[node]))) {
      if(is_vis[child]) {
        low[node] = min(low[node], entry[child]);
      } else {
        is_vis[child] = true;
        parent[child] = node;
        depth[child] = depth[node] + 1;
        entry[child] = exit[node];

        self(child);

        size[node] += size[child];
        exit[node] = exit[child] + 1;
        low[node] = min(low[node], low[child]);
      }
    }

    post_order.push_back(node);
  });
  is_vis[root] = true;
  parent[root] = -1;
  depth[root] = 0;
  entry[root] = 0;
  walk(root);

  return {
    is_vis,
    parent, depth, size,
    entry, exit, low,
    pre_order, post_order
  };
}
