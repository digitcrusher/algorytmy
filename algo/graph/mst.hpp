/*
 * Minimalne drzewo rozpinające - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "ds/dsu/standard.hpp"
#include <algorithm>
#include <climits>
#include <queue>
#include <vector>

struct Edge {
  int a, b;
  ll cost;
};
struct MST {
  vector<Edge> edges;
  ll cost;
};

/*
 * Algorytm Kruskala -
 *   Znajduje minimalny las rozpinający grafu nieskierowanego w O(E log V).
 */
MST mst_kruskal(int nodec, vector<Edge> edges) {
  MST mst;
  mst.edges.reserve(nodec - 1);
  mst.cost = 0;

  sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
    return a.cost < b.cost;
  });

  DSU connected(nodec);
  for(auto edge: edges) {
    if(connected.setc == 1) break;
    if(connected.merge(edge.a, edge.b)) {
      mst.edges.push_back(edge);
      mst.cost += edge.cost;
    }
  }

  mst.edges.shrink_to_fit();
  return mst;
}

/*
 * Algorytm Prima -
 *   Znajduje minimalny las rozpinający grafu nieskierowanego w O(E log V).
 */
MST mst_prim(vector<vector<Edge>> const& incident) {
  int const n = incident.size();

  MST mst;
  mst.edges.reserve(n - 1);
  mst.cost = 0;

  vector is_vis(n, false);
  for(int root = 0; root < n; root++) {
    if(is_vis[root]) continue;

    auto cmp = [](Edge a, Edge b) {
      return a.cost > b.cost;
    };
    priority_queue<Edge, vector<Edge>, decltype(cmp)> q(cmp);

    is_vis[root] = true;
    for(auto edge: incident[root]) {
      q.push(edge);
    }

    while(!q.empty()) {
      auto edge = q.top();
      q.pop();

      if(is_vis[edge.a] && is_vis[edge.b]) continue;
      mst.edges.push_back(edge);
      mst.cost += edge.cost;

      auto unvisited = is_vis[edge.a] ? edge.b : edge.a;
      is_vis[unvisited] = true;
      for(auto edge: incident[unvisited]) {
        q.push(edge);
      }
    }
  }

  mst.edges.shrink_to_fit();
  return mst;
}

MST mst_prim(vector<vector<pair<int, ll>>> const& adj) {
  int const n = adj.size();

  MST mst;
  mst.edges.reserve(n - 1);
  mst.cost = 0;

  vector<ll> cost(n, LLONG_MAX);
  vector<int> prev(n);
  for(int root = 0; root < n; root++) {
    if(cost[root] != LLONG_MAX) continue;

    using QueueElem = pair<ll, int>;
    priority_queue<QueueElem, vector<QueueElem>, greater<QueueElem>> q;

    cost[root] = 0;
    q.push({0, root});

    while(!q.empty()) {
      auto [cost_in_q, node] = q.top();
      q.pop();

      if(cost_in_q != cost[node]) continue;
      if(node != root) {
        mst.edges.push_back({prev[node], node, cost[node]});
        mst.cost += cost[node];
      }
      cost[node] = LLONG_MIN;

      for(auto [neighbor, edge_cost]: adj[node]) {
        if(cost[neighbor] > edge_cost) {
          cost[neighbor] = edge_cost;
          prev[neighbor] = node;
          q.push({cost[neighbor], neighbor});
        }
      }
    }
  }

  mst.edges.shrink_to_fit();
  return mst;
}
