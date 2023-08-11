/*
 * Ścieżki - digitcrusher/algorytmy
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
#include <functional>
#include <optional>
#include <vector>

/*
 * Oblicza liczbę ścieżek z wierzchołka src do każdego innego w DAGu w O(V + E).
 * Na wejściu przyjmuje graf z odwróconymi krawędziami. Ten problem dla
 * ogólniejszych grafów jest #P-zupełny.
 */
vector<ll> count_paths_dag(vector<vector<int>> const& rev_adj, int src) {
  int const n = rev_adj.size();

  vector<ll> result(n, -1);
  result[src] = 1;

  function<void(int)> dfs = [&](int node) {
    if(result[node] != -1) return;
    result[node] = 0;
    for(auto parent: rev_adj[node]) {
      dfs(parent);
      result[node] += result[parent];
    }
  };
  for(int root = 0; root < n; root++) {
    dfs(root);
  }

  return result;
}

/*
 * Znajduje najdłuższą ścieżkę pomiędzy dwoma wierzchołkami w DAGu w O(V + E).
 * Ten problem dla ogólniejszych grafów jest NP-trudny.
 */
optional<vector<int>> longest_path_dag(vector<vector<int>> const& adj, int from, int to) {
  int const n = adj.size();

  vector<int> dist(n, -1), next(n);
  dist[to] = 0;
  next[to] = -1;

  function<void(int)> calc = [&](int node) {
    if(dist[node] != -1) return;
    dist[node] = INT_MIN;
    for(auto child: adj[node]) {
      calc(child);
      if(dist[node] < dist[child] + 1) {
        dist[node] = dist[child] + 1;
        next[node] = child;
      }
    }
  };
  calc(from);

  if(dist[from] < 0) {
    return nullopt;
  } else {
    vector<int> result;
    result.reserve(dist[from] + 1);
    for(auto node = from; node != -1; node = next[node]) {
      result.push_back(node);
    }
    return result;
  }
}

/*
 * Dla każdego wierzchołka w drzewie oblicza odległość do najbardziej
 * oddalonego (jednego z punktów średnicy) i znajduje średnicę w O(V).
 */
struct MaxDistTree {
  vector<int> max_dist;
  int a, b;
};
MaxDistTree max_dist_tree(vector<vector<int>> const& adj) {
  int const n = adj.size();

  vector<int> max_dist(n, 0);

  function<int(int, int, int)> dfs = [&](int node, int parent, int dist) {
    max_dist[node] = max(max_dist[node], dist);
    auto farthest = node;
    for(auto child: adj[node]) {
      if(child == parent) continue;
      auto sub = dfs(child, node, dist + 1);
      if(max_dist[sub] >= max_dist[farthest]) {
        farthest = sub;
      }
    }
    return farthest;
  };

  auto a = dfs(0, -1, 0);
  auto b = dfs(a, -1, 0);
  dfs(b, -1, 0);

  return {max_dist, a, b};
}
