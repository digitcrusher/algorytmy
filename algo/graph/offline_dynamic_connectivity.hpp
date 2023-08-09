/*
 * Offline dynamic connectivity - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "ds/dsu/undoable.hpp"
#include "math/int.hpp"
#include "misc.hpp"
#include <functional>
#include <unordered_map>
#include <vector>

/*
 * Offline dynamic connectivity -
 *   Sztuczka pozwalająca na analizowanie spójności grafu po każdej operacji
 *   dodania lub usunięcia krawędzi offline w O(q log q log n).
 */
struct Query {
  enum {
    add, remove, are_connected
  } type;
  int a, b;
};
vector<bool> offline_dynamic_connectivity(int n, vector<Query> const& queries) {
  int const q = queries.size();

  int height = ceil_log2(q) + 1;
  int nodec = (1u << height) - 1;
  int base_nodec = 1u << (height - 1);
  int base_offset = (1u << (height - 1)) - 1;
  vector<vector<pair<int, int>>> tree(nodec);

  auto add = [&](int l, int r, pair<int, int> edge) {
    function<void(int, int, int)> descend = [&](int num, int node_l, int node_r) {
      if(l <= node_l && node_r <= r) {
        tree[num - 1].push_back(edge);
      } else if(!(node_r < l || r < node_l)) {
        int mid = (node_l + node_r) / 2;
        descend(2 * num, node_l, mid);
        descend(2 * num + 1, mid + 1, node_r);
      }
    };
    descend(1, 0, base_nodec - 1);
  };

  unordered_map<pair<int, int>, int> edge_add_time;
  for(int i = 0; i < q; i++) {
    auto [type, a, b] = queries[i];
    if(a > b) {
      swap(a, b);
    }
    if(type == Query::add) {
      edge_add_time[{a, b}] = i;
    } else if(type == Query::remove) {
      add(edge_add_time[{a, b}], i - 1, {a, b});
      edge_add_time.erase({a, b});
    }
  }
  for(auto [edge, add_time]: edge_add_time) {
    add(add_time, q - 1, edge);
  }

  vector<bool> results;
  results.reserve(q);

  UndoableDSU dsu(n);
  function<void(int, int, int)> calc = [&](int num, int node_l, int node_r) {
    if(q <= node_l) return;
    for(auto [a, b]: tree[num - 1]) {
      dsu.merge(a, b);
    }
    if(num - 1 >= base_offset) {
      auto [type, a, b] = queries[num - 1 - base_offset];
      if(type == Query::are_connected) {
        results.push_back(dsu.find(a) == dsu.find(b));
      }
    } else {
      int mid = (node_l + node_r) / 2;
      calc(2 * num, node_l, mid);
      calc(2 * num + 1, mid + 1, node_r);
    }
    for(int i = 0; i < tree[num - 1].size(); i++) {
      dsu.undo();
    }
  };
  calc(1, 0, base_nodec - 1);

  return results;
}
