/*
 * Rozwiązanie zadania "Małpki" z Solve w czasie O(n log n)
 * z użyciem struktury zbiorów rozłącznych
 *                                   digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#include "common.hpp"
#include "iostream.hpp"
#include <set>

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> malpka_paws(n);
  multiset<pair<int, int>> grips_set;
  for(auto i: v::iota(0, n)) {
    auto &[l, r] = malpka_paws[i];
    cin >> l >> r;
    if(l != -1) {
      l--;
      grips_set.insert({min(i, l), max(i, l)});
    }
    if(r != -1) {
      r--;
      grips_set.insert({min(i, r), max(i, r)});
    }
  }

  vector<pair<int, int>> let_gos(m);
  for(auto i: v::iota(0, m)) {
    auto &[a, b] = let_gos[i];
    cin >> a >> b;
    a--;
    b = b == 1 ? malpka_paws[a].first : malpka_paws[a].second;
    if(a > b) {
      swap(a, b);
    }

    grips_set.erase(grips_set.find(let_gos[i]));
  }

  constexpr auto never = INT_MAX;
  vector fall_times(n, -1);
  fall_times[0] = never;

  vector<int> dsu(n);
  iota(dsu.begin(), dsu.end(), 0);
  auto find = Y([&](auto &self, int malpka) -> int {
    if(dsu[malpka] == malpka) {
      return malpka;
    } else {
      auto repr = self(dsu[malpka]);
      if(fall_times[malpka] == -1) {
        fall_times[malpka] = fall_times[dsu[malpka]];
      }
      dsu[malpka] = repr;
      return repr;
    }
  });

  for(auto grip: grips_set) {
    auto a = find(grip.first), b = find(grip.second);
    if(a == b) continue;
    if(fall_times[a] > fall_times[b]) {
      swap(a, b);
    }
    dsu[a] = b;
  }
  for(auto i: v::iota(0, m) | v::reverse) {
    auto a = find(let_gos[i].first), b = find(let_gos[i].second);
    if(a == b) continue;
    if(fall_times[a] > fall_times[b]) {
      swap(a, b);
    }
    if(fall_times[a] == -1 && fall_times[b] != -1) {
      fall_times[a] = i;
    }
    dsu[a] = b;
  }

  for(auto i: v::iota(0, n)) {
    find(i);
    if(fall_times[i] == never) {
      cout << "-1\n";
    } else {
      cout << fall_times[i] << "\n";
    }
  }
}
