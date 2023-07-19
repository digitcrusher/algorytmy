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
vector<ll> count_paths(vector<vector<int>> const& rev_adj, int src) {
  int const n = rev_adj.size();

  vector<ll> cnt(n, -1);
  cnt[src] = 1;

  function<void(int)> dfs = [&](int node) {
    if(cnt[node] != -1) return;
    cnt[node] = 0;
    for(auto parent: rev_adj[node]) {
      dfs(parent);
      cnt[node] += cnt[parent];
    }
  };
  for(int root = 0; root < n; root++) {
    dfs(root);
  }

  return cnt;
}

/*
 * Znajduje najdłuższą ścieżkę pomiędzy dwoma wierzchołkami w DAGu w O(V + E).
 * Ten problem dla ogólniejszych grafów jest NP-trudny.
 */
optional<vector<int>> longest_path(vector<vector<int>> const& adj, int from, int to) {
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
    for(int node = from; node != -1; node = next[node]) {
      result.push_back(node);
    }
    return result;
  }
}
