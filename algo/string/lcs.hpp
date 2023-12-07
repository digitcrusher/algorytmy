/*
 * Najdłuższy wspólny podciąg - digitcrusher/algorytmy
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
#include <numeric>
#include <string>
#include <vector>

/*
 * Oblicza długość najdłuższego wspólnego podciągu a i b
 * w O(a * b) z zużyciem pamięci O(min(a, b)).
 */
int lcs_len(string const& _a, string const& _b) {
  string const& a = _a.size() >= _b.size() ? _a : _b;
  string const& b = _b.size() <= _a.size() ? _b : _a;
  int const n = a.size(), m = b.size();

  vector curr(m + 1, 0), prev(m + 1, 0);
  for(auto i: v::iota(1, n + 1)) {
    swap(curr, prev);
    for(auto j: v::iota(1, m + 1)) {
      curr[j] = max(prev[j], curr[j - 1]);
      if(a[i - 1] == b[j - 1]) {
        curr[j] = max(curr[j], prev[j - 1] + 1);
      }
    }
  }

  return curr[m];
}

/*
 * Oblicza długość najdłuższego wspólnego podciągu dla każdej pary
 * prefiksów a i prefiksów b w O(a * b) z zużyciem pamięci O(a * b).
 */
vector<vector<int>> lcs_dp(string const& a, string const& b) {
  int const n = a.size(), m = b.size();

  vector dp(n + 1, vector(m + 1, 0));
  for(auto i: v::iota(1, n + 1)) {
    for(auto j: v::iota(1, m + 1)) {
      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      if(a[i - 1] == b[j - 1]) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
      }
    }
  }

  return dp;
}

/*
 * Znajduje najdłuższy wspólny podciąg prefiksu a o długości n i
 * prefiksu b o długości m na podstawie wyniku lcs_dp(a, b) w O(n + m).
 */
string lcs_str(string const& a, string const& b,
               vector<vector<int>> const& dp,
               int n = -1, int m = -1)
{
  n = n == -1 ? a.size() : n;
  m = m == -1 ? b.size() : m;

  string result;
  while(n > 0 && m > 0) {
    if(a[n - 1] == b[m - 1]) {
      result.push_back(a[n - 1]);
      n--, m--;
    } else if(dp[n - 1][m] >= dp[n][m - 1]) {
      n--;
    } else {
      m--;
    }
  }
  r::reverse(result);

  return result;
}

/*
 * Znajduje najdłuższy wspólny podciąg a i b
 * w O(a * b) z zużyciem pamięci O(min(a, b)).
 */
string lcs_str(string const& _a, string const& _b) {
  auto const& a = _a.size() >= _b.size() ? _a : _b;
  auto const& b = _b.size() <= _a.size() ? _b : _a;
  auto are_swapped = _a.size() < _b.size();

  string result;
  auto path_i = 0, path_j = 0;
  auto move = [&](int i, int j) {
    if(i == path_i + 1 && j == path_j + 1) {
      result.push_back(a[i - 1]);
    }
    path_i = i, path_j = j;
  };

  auto conquer = Y([&](auto &self, int a1, int b1, int a2, int b2) -> void {
    auto const n = a2 - a1, m = b2 - b1;

    if(n <= 1) {
      auto did_match = false;
      for(auto j: v::iota(b1 + 1, b2 + 1)) {
        did_match |= a2 > 0 && a[a2 - 1] == b[j - 1];
        move(did_match ? a2 : a1, j);
      }
      return;
    }
    if(m <= 1) {
      auto did_match = false;
      for(auto i: v::iota(a1 + 1, a2 + 1)) {
        did_match |= b2 > 0 && a[i - 1] == b[b2 - 1];
        move(i, did_match ? b2 : b1);
      }
      return;
    }

    vector<int> mid(m + 1), prev_mid(m + 1, 0);
    vector dp(m + 1, 0), prev_dp(m + 1, 0);
    iota(mid.begin(), mid.end(), 0);

    for(auto i: v::iota(1, n + 1)) {
      swap(dp, prev_dp);
      if(i > n / 2) {
        swap(mid, prev_mid);
      }

      for(auto j: v::iota(1, m + 1)) {
        dp[j] = max(prev_dp[j], dp[j - 1]);
        if(a[a1 + i - 1] == b[b1 + j - 1]) {
          dp[j] = max(dp[j], prev_dp[j - 1] + 1);
        }

        if(i > n / 2) {
          if(a[a1 + i - 1] == b[b1 + j - 1]) {
            mid[j] = prev_mid[j - 1];
          } else if((!are_swapped && prev_dp[j] >= dp[j - 1]) || (are_swapped && prev_dp[j] > dp[j - 1])) {
            mid[j] = prev_mid[j];
          } else {
            mid[j] = mid[j - 1];
          }
        }
      }
    }

    auto mid_i = a1 + n / 2, mid_j = b1 + mid[m];
    self(a1, b1, mid_i, mid_j);
    move(mid_i, mid_j);
    self(mid_i, mid_j, a2, b2);
  });

  conquer(0, 0, a.size(), b.size());
  move(a.size(), b.size());

  return result;
}
