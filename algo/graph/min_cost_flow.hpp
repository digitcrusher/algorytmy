/*
 * Przepływ minimalnego kosztu - digitcrusher/algorytmy
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
 * Przepływ minimalnego kosztu z metodą Forda-Fulkersona i SPFA -
 *   Znajduje najtańszy przepływ o danym rozmiarze w grafie skierowanym
 *   w czasie O(F * V * E). W grafie z ujemnym cyklem nie zatrzyma się.
 */
struct MinCostFlow {
  vector<vector<int>> flow;
  int global_flow;
  ll global_cost;
};
struct Edge {
  int other, cap;
  ll cost;
  int flow = 0;
};
MinCostFlow min_cost_flow(vector<vector<Edge>> adj, int src, int sink, int desired_flow) {
  int n = adj.size();

  vector flow(n, vector(n, 0));
  auto global_flow = 0;
  ll global_cost = 0;

  vector<vector<pair<int, int>>> rev_adj(n);
  for(auto a: v::iota(0, n)) {
    for(auto i: v::iota(0, (int) adj[a].size())) {
      auto b = adj[a][i].other;
      rev_adj[b].emplace_back(a, i);
    }
  }

  while(global_flow < desired_flow) {
    vector<ll> path_cost(n, LLONG_MAX);
    vector<int> path_cap(n);
    struct Prev {
      int node;
      Edge *edge;
      bool is_rev;
    };
    vector<Prev> prev(n);
    queue<int> q;
    vector is_in_q(n, false);

    path_cost[src] = 0;
    path_cap[src] = INT_MAX;
    q.push(src);
    is_in_q[src] = true;

    while(!q.empty()) {
      auto node = q.front();
      q.pop();
      is_in_q[node] = false;

      auto relax = [&](int neighbor, int cap, ll cost, Edge &edge, bool is_rev) {
        if(cap <= 0) return;
        auto new_cost = path_cost[node] + cost;
        auto new_cap = min(path_cap[node], cap);
        if(path_cost[neighbor] > new_cost || (path_cost[neighbor] == new_cost && path_cap[neighbor] < new_cap)) {
          path_cost[neighbor] = new_cost;
          path_cap[neighbor] = new_cap;
          prev[neighbor] = {node, &edge, is_rev};
          if(!is_in_q[neighbor]) {
            q.push(neighbor);
            is_in_q[neighbor] = true;
          }
        }
      };
      for(auto &edge: adj[node]) {
        relax(edge.other, edge.cap - edge.flow, edge.cost, edge, false);
      }
      for(auto [neighbor, idx]: rev_adj[node]) {
        auto &edge = adj[neighbor][idx];
        relax(neighbor, edge.flow, -edge.cost, edge, true);
      }
    }

    auto new_flow = min(path_cap[sink], desired_flow - global_flow);
    if(new_flow <= 0) break;
    global_flow += new_flow;
    global_cost += new_flow * path_cost[sink];

    for(auto node = sink; node != src; node = prev[node].node) {
      prev[node].edge->flow += new_flow * (prev[node].is_rev ? -1 : 1);
      flow[prev[node].node][node] += new_flow;
      flow[node][prev[node].node] -= new_flow;
    }
  }

  return {flow, global_flow, global_cost};
}
