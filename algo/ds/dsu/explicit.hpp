/*
 * Struktura zbiorów rozłącznych z trzymaniem elementów - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <vector>

/*
 * Struktura zbiorów rozłącznych z trzymaniem elementów -
 *   Struktura pozwalająca na operacje znajdywania zbioru, do którego należy
 *   dany element (find) w O(1), łączenia dwóch zbiorów (merge) w zamortyzowanym
 *   czasie O(log n) i przeglądanie elementów zbiorów.
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
    for(auto i: sets[b]) {
      parent[i] = a;
      sets[a].push_back(i);
    }
    sets[b].clear();
    sets[b].shrink_to_fit();
    return true;
  }
};
