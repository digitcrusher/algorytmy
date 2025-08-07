/*
 * Najniższy wspólny przodek - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "ds/sparse_table.hpp"

/*
 * Znajduje najniższego wspólnego przodka dwóch wierzchołków
 * w drzewie na podstawie jego binary liftingu w O(log V).
 */
int lca_lifting(vector<int> const& parent, vector<int> const& lift,
                vector<int> const& depth, int a, int b)
{
  if(depth[a] < depth[b]) {
    swap(a, b);
  }
  while(depth[a] > depth[b]) {
    if(depth[lift[a]] >= depth[b]) {
      a = lift[a];
    } else {
      a = parent[a];
    }
  }

  while(a != b) {
    if(lift[a] != lift[b]) {
      a = lift[a];
      b = lift[b];
    } else {
      a = parent[a];
      b = parent[b];
    }
  }
  return a;
}

/*
 * Znajduje najniższego wspólnego przodka dwóch wierzchołków
 * w drzewie na podstawie jego gorszego binary liftingu w O(log V).
 */
int lca_worse_lifting(vector<vector<int>> const& lift,
                      vector<int> const& depth, int a, int b)
{
  if(depth[a] < depth[b]) {
    swap(a, b);
  }

  int max_jump = INT_MAX;
  while(depth[a] > depth[b]) {
    auto jump = min<int>(max_jump, lift[a].size() - 1);
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
    auto jump = min(max_jump, min<int>(lift[a].size(), lift[b].size()) - 1);
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
  int n = adj.size();

  vector<int> entry(n), depth(n);
  vector<int> euler_tour;
  euler_tour.reserve(2 * n - 1);

  auto dfs = Y([&](auto &self, int node, int parent) -> void {
    entry[node] = euler_tour.size();
    euler_tour.push_back(node);
    for(auto child: adj[node] | v::filter(λ(_ != parent))) {
      depth[child] = depth[node] + 1;
      self(child, node);
      euler_tour.push_back(node);
    }
  });
  depth[root] = 0;
  dfs(root, -1);

  auto sum = λ2(r::min(_1, _2, {}, λ(depth[_])));
  SparseTable<int, decltype(sum)> rmq(euler_tour, sum);

  return rmq.get(min(entry[a], entry[b]), max(entry[a], entry[b]));
}
