/*
 * Centroid decomposition - digitcrusher/algorytmy
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
 * Centroid decomposition -
 *   Rozkłada drzewo nieskierowane na ukorzenione drzewo centroidów oryginalnego
 *   grafu w O(V * h) = O(V log V), gdzie h to wysokość wynikowego drzewa.
 */
struct CentroidDecomp {
  vector<int> parent;
  vector<vector<int>> children;
};
CentroidDecomp centroid_decomp(vector<vector<int>> const& adj) {
  int const n = adj.size();

  CentroidDecomp decomp;
  decomp.parent.resize(n, -2);
  decomp.children.resize(n);

  vector<int> size(n);
  auto calc_size = Y([&](auto &self, int node, int parent) -> void {
    size[node] = 1;
    for(auto child: adj[node] | v::filter(λ(_ != parent && decomp.parent[_] == -2))) {
      self(child, node);
      size[node] += size[child];
    }
  });

  auto find_centroid = Y([&](auto &self, int node, int parent, int subgraph_size) -> int {
    auto it = r::find_if(adj[node], λ(_ != parent && decomp.parent[_] == -2 && size[_] > subgraph_size / 2));
    return it == adj[node].end() ? node : self(*it, node, subgraph_size);
  });

  auto decompose = Y([&](auto &self, int node, int parent) -> void {
    calc_size(node, -1);
    auto centroid = find_centroid(node, -1, size[node]);
    decomp.parent[centroid] = parent;
    if(parent != -1) {
      decomp.children[parent].push_back(centroid);
    }

    for(auto child: adj[centroid] | v::filter(λ(decomp.parent[_] == -2))) {
      self(child, centroid);
    }
  });

  for(auto root: v::iota(0, n) | v::filter(λ(decomp.parent[_] == -2))) {
    decompose(root, -1);
  }

  return decomp;
}
