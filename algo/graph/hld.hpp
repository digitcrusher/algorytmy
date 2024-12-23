/*
 * Heavy-light decomposition - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "graph/binary_lift.hpp"
#include "graph/lca.hpp"

/*
 * Heavy-light decomposition (HLD) -
 *   Rozkłada ukorzenione drzewo na "ciężkie" ścieżki w O(V) tak, że na każdej
 *   ścieżce z dowolnego wierzchołka do korzenia jest O(log V) ciężkich ścieżek,
 *   oraz przypisuje wierzchołkom numerację preorder tak, że kolejne wierzchołki
 *   na cięzkiej ścieżce mają przypisane kolejne liczby całkowite dodatnie.
 */
struct HLD {
  int root;
  vector<int> size, parent, heavy, entry;

  // Preprocessing potrzebny do znajdywania najniższego wspólnego przodka
  vector<int> lift, depth;

  HLD(vector<vector<int>> adj, int root): root(root) {
    int n = adj.size();

    size.resize(n, -1);
    parent.resize(n);
    depth.resize(n);
    auto calc_size = Y([&](auto &self, int node) -> void {
      size[node] = 1;
      auto is_first_child = true;
      for(auto &child: adj[node] | v::filter(λ(size[_] == -1))) {
        parent[child] = node;
        depth[child] = depth[node] + 1;

        self(child);

        size[node] += size[child];
        if(is_first_child || size[child] > size[adj[node][0]]) {
          swap(child, adj[node][0]);
        }
        is_first_child = false;
      }
    });
    parent[root] = -1;
    depth[root] = 0;
    calc_size(root);

    heavy.resize(n, -1);
    entry.resize(n);
    auto time = 0;
    auto decompose = Y([&](auto &self, int node) -> void {
      entry[node] = time;
      time++;

      auto is_first_child = true;
      for(auto child: adj[node] | v::filter(λ(heavy[_] == -1))) {
        heavy[child] = is_first_child ? heavy[node] : child;
        self(child);
        is_first_child = false;
      }
    });
    heavy[root] = root;
    decompose(root);

    lift = binary_lift(parent);
  }

  int node(int node) const {
    return entry[node];
  }

  vector<pair<int, int>> path(int a, int b) const {
    vector<pair<int, int>> result;

    auto lca = lca_lifting(parent, lift, depth, a, b);

    while(true) {
      auto l = entry[heavy[a] == heavy[lca] ? lca : heavy[a]];
      auto r = entry[a];
      result.emplace_back(l, r);
      if(heavy[a] == heavy[lca]) break;
      a = parent[heavy[a]];
    }
    while(b != lca) {
      auto l = heavy[b] == heavy[lca] ? entry[lca] + 1 : entry[heavy[b]];
      auto r = entry[b];
      result.emplace_back(l, r);
      if(heavy[b] == heavy[lca]) break;
      b = parent[heavy[b]];
    }

    return result;
  }

  pair<int, int> subtree(int node) const {
    return {entry[node], entry[node] + size[node] - 1};
  }
};
