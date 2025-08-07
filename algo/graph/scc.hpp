/*
 * Silnie spójne składowe - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"

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
  int n = adj.size();

  vector is_vis(n, false);
  vector<int> post_order;
  post_order.reserve(n);

  auto dfs1 = Y([&](auto &self, int node) -> void {
    if(is_vis[node]) return;
    is_vis[node] = true;

    for(auto child: adj[node]) {
      self(child);
    }
    post_order.push_back(node);
  });
  for(auto node: v::iota(0, n)) {
    dfs1(node);
  }

  auto scc_cnt = 0;
  vector node_scc(n, -1);
  vector<vector<int>> scc_adj;
  scc_adj.reserve(n);

  auto dfs2 = Y([&](auto &self, int node) -> void {
    for(auto parent: rev_adj[node]) {
      if(node_scc[parent] == -1) {
        node_scc[parent] = node_scc[node];
        self(parent);
      } else if(node_scc[parent] != node_scc[node]) {
        scc_adj[node_scc[parent]].push_back(node_scc[node]);
      }
    }
  });
  for(auto node: post_order | v::reverse | v::filter(λ(node_scc[_] == -1))) {
    node_scc[node] = scc_cnt;
    scc_cnt++;
    scc_adj.emplace_back();
    dfs2(node);
  }

  scc_adj.shrink_to_fit();

  return {scc_cnt, node_scc, scc_adj};
}
