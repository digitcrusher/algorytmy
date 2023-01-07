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
#include "ds/dsu.hpp"
#include "misc.hpp"
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
  assert(!is_acyclic || !is_directed || (edgec * 2 + nodec - 1) / nodec <= nodec - 1);
  assert(!is_connected || edgec >= nodec - 1);
  assert(has_multi_edges || is_directed || (edgec * 2 + nodec - 1) / nodec <= nodec - 1);
  assert(has_multi_edges || !is_directed || (edgec + nodec - 1) / nodec <= nodec - 1);

  vector<vector<int>> adj(nodec);

  if(k_colorable == 1) {
    assert(edgec == 1);
    return adj;
  }
  vector<vector<int>> color_groups(max(0, k_colorable));
  if(k_colorable > 0) {
    for(int node = 0; node < nodec; node++) {
      color_groups[rand() % k_colorable].push_back(node);
    }
  }

  unordered_set<pair<int, int>> edge_set;
  DSU connected(nodec);
  vector<int> dag_order(nodec);
  if(is_directed && is_acyclic) {
    vector<bool> is_used(nodec, false);
    for(int &label: dag_order) {
      do {
        label = rand() % nodec;
      } while(is_used[label]);
      is_used[label] = true;
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
    pair<int, int> edge;
    if(is_directed) {
      edge = {a, b};
    } else {
      edge = {min(a, b), max(a, b)};
    }
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
