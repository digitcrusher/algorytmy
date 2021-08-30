/*
 * Rozwiązanie zadania "Kajaki" z IV OI działające w czasie O(n^2.5)
 * przy użyciu skojarzeń w grafie dwudzielnym
 *                                            digitcrusher/algorytmy
 *
 * Copyright (c) 2021 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#include "common.hpp"
#include "graph/matching.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int w, n;
  cin >> w >> n;
  vector<int> kajaks(n);
  for(auto &kajak: kajaks) {
    cin >> kajak;
  }

  sort(kajaks.begin(), kajaks.end());

  vector<vector<int>> adj(n);
  vector<int> smalls, bigs;
  for(int i = 0; i < n; i++) {
    if(kajaks[i] <= w / 2) {
      smalls.push_back(i);

      for(int j = n - 1; j >= 0; j--) {
        if(kajaks[j] <= w / 2) break;
        if(kajaks[i] + kajaks[j] > w) continue;
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
    } else {
      bigs.push_back(i);
    }
  }
  auto matching = match_hopcroft_karp(adj, smalls, bigs);

  int result = n - matching.pairc;
  int c = 0;
  for(int i = 0; i < n; i++) {
    if(kajaks[i] > w / 2) break;
    if(matching.pair[i] == -1) {
      c++;
    }
  }
  result -= c / 2;
  cout << result << "\n";
}
