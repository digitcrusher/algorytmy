/*
 * Struktura zbiorów rozłącznych z cofaniem - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <stack>
#include <vector>

/*
 * Las zbiorów rozłącznych z cofaniem -
 *   Struktura pozwalająca na operacje znajdywania zbioru, do którego należy
 *   dany element, (find), łączenia dwóch zbiorów (merge) w O(log n) i cofnięcia
 *   ostatniej operacji (undo) w O(1). Zużywa O(n) pamięci.
 */
struct UndoableDSU {
  int elemc, setc;
  vector<int> parent, size;
  stack<pair<int, int>> merges;

  UndoableDSU(int cnt): elemc(cnt), setc(cnt), parent(cnt), size(cnt, 1) {
    for(int i = 0; i < elemc; i++) {
      parent[i] = i;
    }
  }

  int find(int node) {
    return parent[node] == node ? node : find(parent[node]);
  }

  bool merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) {
      merges.push({-1, -1});
      return false;
    }
    setc--;
    if(size[a] < size[b]) {
      swap(a, b);
    }
    parent[b] = a;
    size[a] += size[b];
    merges.push({a, b});
    return true;
  }

  bool undo() {
    auto [a, b] = merges.top();
    merges.pop();
    if(a == -1 && b == -1) {
      return false;
    }
    setc++;
    parent[b] = b;
    size[a] -= size[b];
    return true;
  }
};
