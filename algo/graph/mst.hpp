/*
 * Minimalne drzewo rozpinające - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "ds/dsu/standard.hpp"
#include <queue>

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

  r::sort(edges, {}, &Edge::cost);

  DSU connected(nodec);
  for(auto edge: edges | v::take_while(λ(connected.setc > 1))) {
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
  int n = incident.size();

  MST mst;
  mst.edges.reserve(n - 1);
  mst.cost = 0;

  vector is_vis(n, false);
  for(auto root: v::iota(0, n) | v::filter(λ(!is_vis[_]))) {
    auto cmp = λ2(_1.cost > _2.cost);
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
  int n = adj.size();

  MST mst;
  mst.edges.reserve(n - 1);
  mst.cost = 0;

  vector<ll> cost(n, LLONG_MAX);
  vector<int> prev(n);
  for(auto root: v::iota(0, n) | v::filter(λ(cost[_] == LLONG_MAX))) {
    using QueueElem = pair<ll, int>;
    priority_queue<QueueElem, vector<QueueElem>, greater<>> q;

    cost[root] = 0;
    q.emplace(0, root);

    while(!q.empty()) {
      auto [cost_in_q, node] = q.top();
      q.pop();

      if(cost_in_q != cost[node]) continue;
      if(node != root) {
        mst.edges.emplace_back(prev[node], node, cost[node]);
        mst.cost += cost[node];
      }
      cost[node] = LLONG_MIN;

      for(auto [neighbor, edge_cost]: adj[node]) {
        if(cost[neighbor] > edge_cost) {
          cost[neighbor] = edge_cost;
          prev[neighbor] = node;
          q.emplace(cost[neighbor], neighbor);
        }
      }
    }
  }

  mst.edges.shrink_to_fit();
  return mst;
}
