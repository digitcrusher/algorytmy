/*
 * Struktura zbiorów rozłącznych - digitcrusher/algorytmy
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
