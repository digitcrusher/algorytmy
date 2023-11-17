/*
 * Generator grafów losowych - digitcrusher/algorytmy
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
#include "hash.hpp"
#include "math/int.hpp"
#include <cstdlib>
#include <unordered_set>
#include <vector>

/*
 * Generuje listę sąsiedztwa losowego grafu spełniającego podane własności.
 */
vector<vector<int>> gen_graph(int nodec, int edgec,
                              bool is_directed = false, bool has_self_loops = false,
                              bool has_multi_edges = false, bool is_connected = false,
                              bool is_acyclic = false, int k_colorable = -1)
{
  assert(!is_acyclic || !has_self_loops);
  assert(!is_acyclic || is_directed || edgec <= nodec - 1);
  assert(!is_acyclic || !is_directed || ceil_div(edgec * 2, nodec) <= nodec - 1);
  assert(!is_connected || edgec >= nodec - 1);
  assert(has_multi_edges || is_directed || ceil_div(edgec * 2, nodec) <= nodec - 1);
  assert(has_multi_edges || !is_directed || ceil_div(edgec, nodec) <= nodec - 1);

  vector<vector<int>> adj(nodec);

  if(k_colorable == 1) {
    assert(edgec == 0);
    return adj;
  }
  vector<vector<int>> color_groups(max(0, k_colorable));
  if(k_colorable > 0) {
    for(auto node: v::iota(0, nodec)) {
      color_groups[rand() % k_colorable].push_back(node);
    }
  }

  unordered_set<pair<int, int>> edge_set;
  DSU connected(nodec);
  vector<int> dag_order(nodec);
  if(is_directed && is_acyclic) {
    vector is_used(nodec, false);
    for(auto &i: dag_order) {
      do {
        i = rand() % nodec;
      } while(is_used[i]);
      is_used[i] = true;
    }
  }

  while(edgec > 0) {
    int a, b;
    if(k_colorable <= 0) {
      a = rand() % nodec;
      b = rand() % nodec;
    } else {
      int color_a, color_b;
      do {
        color_a = rand() % k_colorable;
        color_b = rand() % k_colorable;
      } while(color_a == color_b);
      auto &group_a = color_groups[color_a];
      auto &group_b = color_groups[color_b];
      a = group_a[rand() % group_a.size()];
      b = group_b[rand() % group_b.size()];
    }

    if(!has_self_loops && a == b) continue;
    auto edge = is_directed ? pair(a, b) : pair(min(a, b), max(a, b));
    if(!has_multi_edges && edge_set.count(edge) != 0) continue;
    if(is_connected && connected.setc > 1 && connected.find(a) == connected.find(b)) continue;
    if(is_acyclic && is_directed && dag_order[a] > dag_order[b]) continue;
    if(is_acyclic && !is_directed && connected.find(a) == connected.find(b)) continue;

    edgec--;
    if(is_directed) {
      adj[a].push_back(b);
    } else {
      adj[a].push_back(b);
      if(a != b) {
        adj[b].push_back(a);
      }
    }
    edge_set.insert(edge);
    connected.merge(a, b);
  }

  return adj;
}
