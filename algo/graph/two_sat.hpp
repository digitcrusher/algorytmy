/*
 * 2-SAT - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "graph/scc.hpp"

/*
 * 2-SAT -
 *   Znajduje jedno z rozwiązań formuły logicznej będącej
 *   koniunkcją m alternatyw nad n literałami w O(n + m).
 */
struct Clause {
  int a;
  bool not_a;
  int b;
  bool not_b;
};
optional<vector<bool>> two_sat(int n, vector<Clause> const& formula) {
  vector<vector<int>> adj(2 * n), rev_adj(2 * n);
  auto implies = [&](int a, bool not_a, int b, bool not_b) {
    auto ai = a + (not_a ? n : 0), bi = b + (not_b ? n : 0);
    adj[ai].push_back(bi);
    rev_adj[bi].push_back(ai);
  };
  for(auto [a, not_a, b, not_b]: formula) {
    implies(a, !not_a, b, not_b);
    implies(b, !not_b, a, not_a);
  }

  auto [_1, scc, _2] = scc_kosaraju(adj, rev_adj);

  vector<bool> result(n);
  for(auto i: v::iota(0, n)) {
    if(scc[i] == scc[i + n]) {
      return nullopt;
    }
    // i może być prawdą, gdy i nie implikuje !i.
    result[i] = !(scc[i] < scc[i + n]);
  }
  return result;
}
