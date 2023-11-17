/*
 * Algorytm Manachera - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <string>
#include <vector>

/*
 * Algorytm Manachera -
 *   Dla każdej pozycji znajduje długość ramion najdłuższego
 *   palindromu wyśrodkowanego w tej pozycji w O(n).
 */
struct Manacher {
  vector<int> odd, even;
};
Manacher manacher(string const& str) {
  int const n = str.size();

  vector<int> odd(n);
  auto l = 0, r = 0;
  for(auto i: v::iota(0, n)) {
    odd[i] = i > r ? 0 : min(r - i, odd[l + r - i]);
    while(0 <= i - odd[i] - 1 && i + odd[i] + 1 < n && str[i - odd[i] - 1] == str[i + odd[i] + 1]) {
      odd[i]++;
    }
    if(r < i + odd[i]) {
      l = i - odd[i];
      r = i + odd[i];
    }
  }

  vector<int> even(n - 1);
  l = 0, r = 0;
  for(auto i: v::iota(0, n - 1)) {
    even[i] = i + 1 > r ? 0 : min(r - i, even[l + r - i - 1]);
    while(0 <= i - even[i] && i + 1 + even[i] < n && str[i - even[i]] == str[i + 1 + even[i]]) {
      even[i]++;
    }
    if(r < i + even[i]) {
      l = i + 1 - even[i];
      r = i + even[i];
    }
  }

  return {odd, even};
}
