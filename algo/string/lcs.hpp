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
#include <functional>
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

  vector<int> curr(m + 1, 0), prev(m + 1, 0);
  for(int i = 1; i <= n; i++) {
    swap(curr, prev);
    for(int j = 1; j <= m; j++) {
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

  vector dp(n + 1, vector<int>(m + 1, 0));
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
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
  reverse(result.begin(), result.end());

  return result;
}

/*
 * Znajduje najdłuższy wspólny podciąg a i b
 * w O(a * b) z zużyciem pamięci O(min(a, b)).
 */
string lcs_str(string const& _a, string const& _b) {
  string const& a = _a.size() >= _b.size() ? _a : _b;
  string const& b = _b.size() <= _a.size() ? _b : _a;
  auto are_swapped = _a.size() < _b.size();

  string result;
  int path_i = 0, path_j = 0;
  auto move = [&](int i, int j) {
    if(i == path_i + 1 && j == path_j + 1) {
      result.push_back(a[i - 1]);
    }
    path_i = i, path_j = j;
  };

  function<void(int, int, int, int)> conquer = [&](int a1, int a2, int b1, int b2) {
    int const n = a2 - a1 + 1, m = b2 - b1 + 1;

    if(n <= 2) {
      auto did_match = false;
      for(int j = b1 + 1; j <= b2; j++) {
        did_match |= a2 > 0 && a[a2 - 1] == b[j - 1];
        move(did_match ? a2 : a1, j);
      }
      return;
    }
    if(m <= 2) {
      auto did_match = false;
      for(int i = a1 + 1; i <= a2; i++) {
        did_match |= b2 > 0 && a[i - 1] == b[b2 - 1];
        move(i, did_match ? b2 : b1);
      }
      return;
    }

    auto mid_i = a1 + n / 2;
    vector<int> mid_j(m), prev_mid_j(m);
    vector<int> dp(m, 0), prev_dp(m);
    for(int j = b1; j <= b2; j++) {
      mid_j[j - b1] = j;
    }
    prev_mid_j[0] = b1;
    dp[0] = 0;

    for(int i = a1 + 1; i <= a2; i++) {
      swap(dp, prev_dp);
      if(i > mid_i) {
        swap(mid_j, prev_mid_j);
      }

      for(int j = b1 + 1; j <= b2; j++) {
        auto k = j - b1;

        dp[k] = max(prev_dp[k], dp[k - 1]);
        if(a[i - 1] == b[j - 1]) {
          dp[k] = max(dp[k], prev_dp[k - 1] + 1);
        }

        if(i > mid_i) {
          if(a[i - 1] == b[j - 1]) {
            mid_j[k] = prev_mid_j[k - 1];
          } else if((!are_swapped && prev_dp[k] >= dp[k - 1]) ||
                    (are_swapped && prev_dp[k] > dp[k - 1])) {
            mid_j[k] = prev_mid_j[k];
          } else {
            mid_j[k] = mid_j[k - 1];
          }
        }
      }
    }

    conquer(a1, mid_i, b1, mid_j[b2 - b1]);
    move(mid_i, mid_j[b2 - b1]);
    conquer(mid_i, a2, mid_j[b2 - b1], b2);
  };

  conquer(0, a.size(), 0, b.size());
  move(a.size(), b.size());

  return result;
}
