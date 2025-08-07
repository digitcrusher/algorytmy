/*
 * Rozwiązanie zadania "Kajaki" z IV OI w czasie O(n^2.5)
 * z użyciem skojarzeń w grafie dwudzielnym
 *                                 digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#include "common.hpp"
#include "graph/matching.hpp"
#include "iostream.hpp"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int w, n;
  cin >> w >> n;
  vector<int> kajaks(n);
  cin >> kajaks;
  r::sort(kajaks);

  vector<vector<int>> adj(n);
  vector<int> smalls, bigs;
  for(auto i: v::iota(0, n)) {
    if(kajaks[i] <= w / 2) {
      smalls.push_back(i);
      for(auto j: v::iota(0, n) | v::reverse | v::take_while(λ(kajaks[_] > w / 2)) | v::drop_while(λ(kajaks[i] + kajaks[_] > w))) {
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
    } else {
      bigs.push_back(i);
    }
  }
  auto matching = match_hopcroft_karp(adj, smalls, bigs);

  auto result = n - matching.pairc - r::count_if(smalls, λ(matching.pair[_] == -1)) / 2;
  cout << result << "\n";
}
