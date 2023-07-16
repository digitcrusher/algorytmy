/*
 * Silnie spójne składowe - digitcrusher/algorytmy
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
 * Algorytm Kosaraju -
 *   Znajduje silnie spójne składowe w grafie skierowanym w czasie O(V + E).
 */
struct SCCs {
  int scc_cnt;
  vector<int> node_scc;
  vector<vector<int>> scc_adj;
};
SCCs scc_kosaraju(vector<vector<int>> const& adj,
                  vector<vector<int>> const& rev_adj)
{
  int const n = adj.size();

  vector<bool> is_vis(n, false);
  vector<int> post_order;
  post_order.reserve(n);

  function<void(int)> dfs1 = [&](int node) {
    if(is_vis[node]) return;
    is_vis[node] = true;
    for(int child: adj[node]) {
      dfs1(child);
    }
    post_order.push_back(node);
  };
  for(int i = 0; i < n; i++) {
    dfs1(i);
  }

  int scc_cnt = 0;
  vector<int> node_scc(n, -1);
  vector<vector<int>> scc_adj;
  scc_adj.reserve(n);

  function<void(int)> dfs2 = [&](int node) {
    for(int parent: rev_adj[node]) {
      if(node_scc[parent] == -1) {
        node_scc[parent] = node_scc[node];
        dfs2(parent);
      } else if(node_scc[parent] != node_scc[node]) {
        scc_adj[node_scc[parent]].push_back(node_scc[node]);
      }
    }
  };
  for(int i = n - 1; i >= 0; i--) {
    int node = post_order[i];
    if(node_scc[node] != -1) continue;
    node_scc[node] = scc_cnt;
    scc_cnt++;
    scc_adj.emplace_back();
    dfs2(node);
  }

  scc_adj.shrink_to_fit();

  return {scc_cnt, node_scc, scc_adj};
}
