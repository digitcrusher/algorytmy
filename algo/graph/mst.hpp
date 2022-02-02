/*
 * Minimalne drzewo spinające - digitcrusher/algorytmy
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
#include "ds/dsu.hpp"
#include <algorithm>
#include <queue>
#include <vector>

struct Edge {
  int a, b;
  int cost;
};
struct MST {
  vector<Edge> edges;
  int cost;
};

/*
 * Algorytm Kruskala -
 *   Znajduje minimalny las spinający grafu nieskierowanego w O(E log V).
 */
MST mst_kruskal(int nodec, vector<Edge> edges) {
  MST mst;
  mst.edges.reserve(nodec - 1);
  mst.cost = 0;

  sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
    return a.cost < b.cost;
  });

  DSU connected(nodec);
  for(Edge edge: edges) {
    if(connected.setc == 1) break;
    if(connected.find(edge.a) == connected.find(edge.b)) continue;
    mst.edges.push_back(edge);
    mst.cost += edge.cost;
    connected.merge(edge.a, edge.b);
  }

  mst.edges.shrink_to_fit();
  return mst;
}

/*
 * Algorytm Prima -
 *   Znajduje minimalny las spinający grafu nieskierowanego w O(E log V).
 */
MST mst_prim(vector<vector<Edge>> const& incident) {
  int const n = incident.size();

  MST mst;
  mst.edges.reserve(n - 1);
  mst.cost = 0;

  vector<bool> is_vis(n, false);
  for(int root = 0; root < n; root++) {
    if(is_vis[root]) continue;

    auto cmp = [](Edge a, Edge b) {
      return a.cost < b.cost;
    };
    priority_queue<Edge, vector<Edge>, decltype(cmp)> q(cmp);

    is_vis[root] = true;
    for(Edge edge: incident[root]) {
      q.push(edge);
    }

    while(!q.empty()) {
      Edge edge = q.top();
      q.pop();

      if(is_vis[edge.a] && is_vis[edge.b]) continue;
      mst.edges.push_back(edge);
      mst.cost += edge.cost;

      int unvisited = is_vis[edge.a] ? edge.b : edge.a;
      is_vis[unvisited] = true;
      for(Edge edge: incident[unvisited]) {
        q.push(edge);
      }
    }
  }

  mst.edges.shrink_to_fit();
  return mst;
}
