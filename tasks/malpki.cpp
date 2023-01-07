/*
 * Rozwiązanie zadania "Małpki" z Solve w czasie O(n log n)
 * z użyciem struktury zbiorów rozłącznych
 *                                   digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#include "common.hpp"
#include <climits>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> malpka_paws(n);
  multiset<pair<int, int>> grips_set;
  for(int i = 0; i < n; i++) {
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
  for(int i = 0; i < m; i++) {
    auto &[a, b] = let_gos[i];
    cin >> a >> b;
    a--;
    b = b == 1 ? malpka_paws[a].first : malpka_paws[a].second;
    if(a > b) {
      swap(a, b);
    }

    grips_set.erase(grips_set.find(let_gos[i]));
  }

  int const never = INT_MAX;
  vector<int> fall_times(n, -1);
  fall_times[0] = never;

  vector<int> dsu(n);
  for(int i = 0; i < n; i++) {
    dsu[i] = i;
  }
  function<int(int)> find = [&](int malpka) {
    if(dsu[malpka] == malpka) {
      return malpka;
    } else {
      int repr = find(dsu[malpka]);
      if(fall_times[malpka] == -1) {
        fall_times[malpka] = fall_times[dsu[malpka]];
      }
      dsu[malpka] = repr;
      return repr;
    }
  };

  for(auto grip: grips_set) {
    int a = find(grip.first), b = find(grip.second);
    if(a == b) continue;
    if(fall_times[a] > fall_times[b]) {
      swap(a, b);
    }
    dsu[a] = b;
  }
  for(int i = m - 1; i >= 0; i--) {
    int a = find(let_gos[i].first), b = find(let_gos[i].second);
    if(a == b) continue;
    if(fall_times[a] > fall_times[b]) {
      swap(a, b);
    }
    if(fall_times[a] == -1 && fall_times[b] != -1) {
      fall_times[a] = i;
    }
    dsu[a] = b;
  }

  for(int i = 0; i < n; i++) {
    find(i);
    if(fall_times[i] == never) {
      cout << "-1\n";
    } else {
      cout << fall_times[i] << "\n";
    }
  }
}
