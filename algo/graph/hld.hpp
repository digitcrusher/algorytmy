/*
 * Heavy-light decomposition - digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include "graph/binary_lift.hpp"
#include "graph/lca.hpp"
#include <functional>
#include <vector>

/*
 * Heavy-light decompostition (HLD) -
 *   Rozkłada ukorzenione drzewo na "ciężkie" ścieżki w O(V) tak, że na każdej
 *   ścieżce z dowolnego wierzchołka do korzenia jest O(log V) ciężkich ścieżek,
 *   oraz przypisuje wierzchołkom numerację preorder tak, że kolejne wierzchołki
 *   na cięzkiej ścieżce mają przypisane kolejne liczby całkowite dodatnie.
 */
struct HLD {
  int root;
  vector<int> size, parent, heavy, entry;

  // Preprocessing potrzebny do znajdywania najniższego wspólnego przodka
  vector<vector<int>> lift;
  vector<int> depth;

  HLD(vector<vector<int>> adj, int root): root(root) {
    int const n = adj.size();

    size.resize(n, -1);
    parent.resize(n);
    depth.resize(n);
    function<void(int)> calc_size = [&](int node) {
      size[node] = 1;
      bool is_first_child = true;
      for(int &child: adj[node]) {
        if(size[child] != -1) continue;

        parent[child] = node;
        depth[child] = depth[node] + 1;

        calc_size(child);

        size[node] += size[child];
        if(is_first_child || size[child] > size[adj[node][0]]) {
          swap(child, adj[node][0]);
        }
        is_first_child = false;
      }
    };
    parent[root] = -1;
    depth[root] = 0;
    calc_size(root);

    heavy.resize(n, -1);
    entry.resize(n);
    int time = 0;
    function<void(int)> decompose = [&](int node) {
      entry[node] = time;
      time++;

      if(adj[node].size() > 1) {
        heavy[adj[node][0]] = heavy[node];
        decompose(adj[node][0]);
      }
      for(int child: adj[node]) {
        if(heavy[child] != -1) continue;
        heavy[child] = child;
        decompose(child);
      }
    };
    heavy[root] = root;
    decompose(root);

    lift = binary_lift(parent);
  }

  vector<pair<int, int>> path(int a, int b) {
    vector<pair<int, int>> result;

    int lca = lca_lifting(lift, depth, a, b);

    while(true) {
      int top = heavy[a] == heavy[lca] ? lca : heavy[a];
      result.push_back({entry[top], entry[a]});
      if(heavy[a] == heavy[lca]) break;
      a = parent[heavy[a]];
    }
    while(b != lca) {
      int l = heavy[b] == heavy[lca] ? entry[lca] + 1 : entry[heavy[b]];
      result.push_back({l, entry[b]});
      if(heavy[b] == heavy[lca]) break;
      b = parent[heavy[b]];
    }

    return result;
  }

  pair<int, int> subtree(int node) {
    return {entry[node], entry[node] + size[node] - 1};
  }
};
