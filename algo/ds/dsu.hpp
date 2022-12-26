/*
 * Struktura zbiorów rozłącznych (Union-Find) - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <vector>

/*
 * Las zbiorów rozłącznych -
 *   Struktura pozwalająca na operacje znajdywania zbioru, do którego należy
 *   dany element, (find) i łączenia dwóch zbiorów (merge) w zamortyzowanym
 *   czasie O(α(n)), czyli praktycznie stałym. Zużywa O(n) pamięci.
 *
 * Wariant bez podpinania mniejszego poddrzewa do większego działa w czasie
 * logarytmicznym.
 */
struct DSU {
  int elemc, setc;
  vector<int> parent, size;

  DSU(int cnt): elemc(cnt), setc(cnt), parent(cnt), size(cnt, 1) {
    for(int i = 0; i < elemc; i++) {
      parent[i] = i;
    }
  }

  int find(int node) {
    if(parent[node] == node) {
      return node;
    } else {
      int repr = find(parent[node]);
      if(parent[node] != repr) {
        size[parent[node]] -= size[node];
        parent[node] = repr;
      }
      return repr;
    }
  }

  bool merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) {
      return false;
    }
    setc--;
    if(size[a] < size[b]) {
      swap(a, b);
    }
    parent[b] = a;
    size[a] += size[b];
    return true;
  }
};

/*
 * Struktura zbiorów rozłącznych z trzymaniem elementów -
 *   Struktura pozwalająca na operacje znajdywania zbioru, do którego należy
 *   dany element (find) w O(1), łączenia dwóch zbiorów (merge) w zamortyzowanym
 *   czasie O(log n) i przeglądanie elementów zbiorów. Zużywa O(n) pamięci.
 */
struct ExplicitDSU {
  int elemc, setc;
  vector<int> parent;
  vector<vector<int>> sets;

  ExplicitDSU(int cnt): elemc(cnt), setc(cnt), parent(cnt), sets(cnt) {
    for(int i = 0; i < elemc; i++) {
      parent[i] = i;
      sets[i].push_back(i);
    }
  }

  int find(int node) {
    return parent[node];
  }

  bool merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) {
      return false;
    }
    setc--;
    if(sets[a].size() < sets[b].size()) {
      swap(a, b);
    }
    sets[a].reserve(sets[a].size() + sets[b].size());
    for(int elem: sets[b]) {
      parent[elem] = a;
      sets[a].push_back(elem);
    }
    sets[b].clear();
    sets[b].shrink_to_fit();
    return true;
  }
};
