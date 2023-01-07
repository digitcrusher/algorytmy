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
#include <functional>
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
  function<void(int, int)> calc_size = [&](int node, int parent) {
    size[node] = 1;
    for(int child: adj[node]) {
      if(child == parent || decomp.parent[child] != -2) continue;
      calc_size(child, node);
      size[node] += size[child];
    }
  };

  function<int(int, int, int)> find_centroid = [&](int node, int parent, int subgraph_size) {
    for(int child: adj[node]) {
      if(child == parent || decomp.parent[child] != -2) continue;
      if(size[child] <= subgraph_size / 2) continue;
      return find_centroid(child, node, subgraph_size);
    }
    return node;
  };

  function<void(int, int)> decompose = [&](int node, int parent) {
    calc_size(node, -1);
    int centroid = find_centroid(node, -1, size[node]);
    decomp.parent[centroid] = parent;
    if(parent != -1) {
      decomp.children[parent].push_back(centroid);
    }

    for(int child: adj[centroid]) {
      if(decomp.parent[child] != -2) continue;
      decompose(child, centroid);
    }
  };

  for(int i = 0; i < n; i++) {
    if(decomp.parent[i] != -2) continue;
    decompose(i, -1);
  }

  return decomp;
}
