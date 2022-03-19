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
  vector<int> size, parent, heavy_path, entry;

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
      for(int i = 0; i < adj[node].size(); i++) {
        int &child = adj[node][i];
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

    heavy_path.resize(n, -1);
    entry.resize(n);
    int time = 0;
    function<void(int)> assign_paths = [&](int node) {
      entry[node] = time;
      time++;

      if(adj[node].size() > 1) {
        heavy_path[adj[node][0]] = heavy_path[node];
        assign_paths(adj[node][0]);
      }
      for(int child: adj[node]) {
        if(heavy_path[child] != -1) continue;
        heavy_path[child] = child;
        assign_paths(child);
      }
    };
    heavy_path[root] = root;
    assign_paths(root);

    lift = binary_lift(parent);
  }

  vector<pair<int, int>> path(int a, int b) {
    vector<pair<int, int>> result;

    int lca = lca_lifting(lift, depth, a, b);

    while(true) {
      int top = heavy_path[a] == heavy_path[lca] ? lca : heavy_path[a];
      result.push_back({entry[top], entry[a]});
      if(heavy_path[a] == heavy_path[lca]) break;
      a = parent[heavy_path[a]];
    }
    while(b != lca) {
      int l = heavy_path[b] == heavy_path[lca] ? entry[lca] + 1 : entry[heavy_path[b]];
      result.push_back({l, entry[b]});
      if(heavy_path[b] == heavy_path[lca]) break;
      b = parent[heavy_path[b]];
    }

    return result;
  }

  pair<int, int> subtree(int node) {
    return {entry[node], entry[node] + size[node] - 1};
  }
};
