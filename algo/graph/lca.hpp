/*
 * Najniższy wspólny przodek - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "ds/sparse_table.hpp"
#include <climits>
#include <functional>
#include <vector>

/*
 * Znajduje najniższego wspólnego przodka dwóch wierzchołków
 * w drzewie na podstawie jego binary liftingu w O(log V).
 */
int lca_lifting(vector<vector<int>> const& lift,
                vector<int> const& depth, int a, int b)
{
  if(depth[a] < depth[b]) {
    swap(a, b);
  }

  int max_jump = INT_MAX;
  while(depth[a] > depth[b]) {
    int jump = min(max_jump, (int) lift[a].size() - 1);
    while(depth[lift[a][jump]] < depth[b]) {
      jump--;
      max_jump = jump;
    }
    a = lift[a][jump];
  }
  if(a == b) {
    return a;
  }

  max_jump = INT_MAX;
  while(lift[a][0] != lift[b][0]) {
    int jump = min(max_jump, (int) min(lift[a].size(), lift[b].size()) - 1);
    while(lift[a][jump] == lift[b][jump]) {
      jump--;
      max_jump = jump;
    }
    a = lift[a][jump];
    b = lift[b][jump];
  }
  return lift[a][0];
}

/*
 * Znajduje najniższego wspólnego przodka dwóch wierzchołków w drzewie przy
 * użyciu dowolnej struktury danych wspierającej operację obliczenia
 * nieznacznie zmodyfikowanego minimum na przedziale po wstępnym
 * przetwarzaniu w O(V).
 */
int lca_rmq(vector<vector<int>> const& adj, int root, int a, int b) {
  int const n = adj.size();

  vector<int> entry(n), depth(n);
  vector<int> euler_tour;
  euler_tour.reserve(2 * n - 1);

  function<void(int, int)> dfs = [&](int node, int parent) {
    entry[node] = euler_tour.size();
    euler_tour.push_back(node);
    for(int child: adj[node]) {
      if(child == parent) continue;
      depth[child] = depth[node] + 1;
      dfs(child, node);
      euler_tour.push_back(node);
    }
  };
  depth[root] = 0;
  dfs(root, -1);

  auto sum = [&](int a, int b) {
    return depth[a] < depth[b] ? a : (depth[a] > depth[b] ? b : min(a, b));
  };
  SparseTable<int, decltype(sum)> rmq(euler_tour, sum);

  return rmq.get(min(entry[a], entry[b]), max(entry[a], entry[b]));
}
