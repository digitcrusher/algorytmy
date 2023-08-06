/*
 * Meet in the middle - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <algorithm>
#include <vector>

/*
 * Meet in the middle -
 *   Technika polegająca na podzieleniu danego problemu na dwa mniejsze
 *   ogólniejsze podproblemy. Poniższy kod jest zastosowaniem jej do
 *   rozwiązania problemu sumy podzbioru w O(n 2^n/2).
 */
ll subset_sum(vector<ll> const& nums, ll target) {
  int const n = nums.size();

  ll result = target == 0 ? -1 : 0;

  auto subsets = [&](int l, int r) {
    vector<ll> sums(1u << r - l + 1, 0);
    for(uint mask = 0; mask < sums.size(); mask++) {
      for(int i = l; i <= r; i++) {
        if(mask & 1u << i - l) {
          sums[mask] += nums[i];
        }
      }
    }
    sort(sums.begin(), sums.end());
    return sums;
  };
  auto left = subsets(0, n / 2 - 1), right = subsets(n / 2, n - 1);

  int i = right.size() - 1, j = right.size() - 1;
  for(auto a: left) {
    while(i >= 0 && a + right[i] >= target) {
      i--;
    }
    while(j >= 0 && a + right[j] > target) {
      j--;
    }
    if(j < 0) break;
    result += j - i;
  }

  return result;
}
