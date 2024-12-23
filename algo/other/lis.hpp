/*
 * Najdłuższy rosnący podciąg - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "ds/segment_tree/point_range.hpp"

/*
 * Znajduje najdłuższy rosnący podciąg w O(n log n).
 */
vector<int> lis(vector<ll> const& nums) {
  int n = nums.size();

  vector<int> dp;
  dp.reserve(n);
  vector<int> prev(n);
  for(auto i: v::iota(0, n)) {
    auto it = r::lower_bound(dp, i, {}, λ(nums[_]));
    if(it == dp.end()) {
      dp.push_back(i);
    } else {
      *it = i;
    }
    if(it == dp.begin()) {
      prev[i] = -1;
    } else {
      prev[i] = *::prev(it);
    }
  }

  vector<int> result(dp.size());
  auto j = dp.back();
  for(auto &i: result | v::reverse) {
    i = j;
    j = prev[j];
  }
  return result;
}

/*
 * Znajduje najdłuższy rosnący podciąg przy użyciu
 * drzewa przedziałowego punkt-przedział w O(n log n).
 */
vector<int> lis_segtree(vector<ll> const& nums) {
  int n = nums.size();

  auto sorted = nums;
  r::sort(sorted);
  int coordc = r::unique(sorted).begin() - sorted.begin();
  sorted.resize(coordc);
  vector<int> coord(n);
  for(auto i: v::iota(0, n)) {
    coord[i] = r::lower_bound(sorted, nums[i]) - sorted.begin();
  }

  vector<int> dp(n), prev(n);
  auto sum = [&](int a, int b) {
    if(a > b) {
      swap(a, b);
    }
    if(a == -1) {
      return b;
    }
    return dp[a] > dp[b] ? a : b;
  };
  SegmentTreePointRange<int, decltype(sum)> tree(vector(coordc, -1), -1, sum);
  for(auto i: v::iota(0, n)) {
    prev[i] = coord[i] == 0 ? -1 : tree.get(0, coord[i] - 1);
    dp[i] = prev[i] == -1 ? 1 : dp[prev[i]] + 1;
    tree.set(coord[i], sum(tree.nodes[tree.base_offset + coord[i]], i));
  }

  auto j = tree.get(0, coordc - 1);
  vector<int> result(dp[j]);
  for(auto &i: result | v::reverse) {
    i = j;
    j = prev[j];
  }
  return result;
}
