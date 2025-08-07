/*
 * Tablica sufiksowa - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "string/prefix_hashes.hpp"

/*
 * Oblicza tablicę sufiksową, czyli tablicę początków posortowanych
 * leksykograficznie sufiksów, przy użyciu podwajania w O(n log n).
 */
vector<int> suffix_array(string const& str) {
  int n = str.size();

  vector<int> result(n);

  auto uniquec = 128;
  vector<int> order(n), cnt(uniquec, 0);
  for(auto i: v::iota(0, n)) {
    order[i] = str[i];
    cnt[order[i]]++;
  }
  partial_sum(cnt.begin(), cnt.end(), cnt.begin());
  for(auto i: v::iota(0, n)) {
    result[--cnt[order[i]]] = i;
  }

  vector<int> temp(n);
  for(auto size = 1; size < n; size *= 2) {
    auto a = n, b = n - size;
    for(auto i: v::iota(0, n)) {
      if(result[i] - size < 0) {
        a--;
        temp[a] = result[i] - size + n;
      } else {
        b--;
        temp[b] = result[i] - size;
      }
    }
    cnt.assign(uniquec, 0);
    for(auto i: order) {
      cnt[i]++;
    }
    partial_sum(cnt.begin(), cnt.end(), cnt.begin());
    for(auto i: temp) {
      result[--cnt[order[i]]] = i;
    }

    uniquec = 0;
    pair prev_key = {-1, -1};
    for(auto i: result) {
      pair key = {order[i], i + size < n ? order[i + size] : -1};
      temp[i] = uniquec - (prev_key == key ? 1 : 0);
      uniquec = temp[i] + 1;
      prev_key = key;
    }
    order.swap(temp);
  }

  return result;
}

/*
 * Algorytm Kasaia -
 *   Oblicza długość najdłuższego wspólnego prefiksu kazdej
 *   sąsiednej pary sufiksów z tablicy sufiksowej w O(n).
 */
vector<int> lcp(string const& str, vector<int> const& suffix_array) {
  int n = str.size();

  vector<int> result(n - 1);

  vector<int> order(n);
  for(auto i: v::iota(0, n)) {
    order[suffix_array[i]] = i;
  }
  auto curr = 0;
  for(auto i: v::iota(0, n)) {
    if(order[i] == n - 1) {
      curr = 0;
      continue;
    }
    auto j = suffix_array[order[i] + 1];
    while(i + curr < n && j + curr < n && str[i + curr] == str[j + curr]) {
      curr++;
    }
    result[order[i]] = curr;
    if(curr > 0) {
      curr--;
    }
  }

  return result;
}

/*
 * Oblicza tablicę sufiksową, czyli tablicę początków posortowanych
 * leksykograficznie sufiksów, przy użyciu podwajania w O(n log^2 n).
 */
vector<int> suffix_array_slower(string const& str) {
  int n = str.size();

  vector<int> result(n);
  iota(result.begin(), result.end(), 0);

  vector<int> order(n + 1);
  for(auto i: v::iota(0, n)) {
    order[i] = str[i];
  }
  order[n] = -1;
  vector<pair<int, int>> keys(n);
  for(auto size = 1; size < n; size *= 2) {
    for(auto i: v::iota(0, n)) {
      keys[i] = {order[i], order[min(i + size, n)]};
    }
    r::sort(result, {}, λ(keys[_]));
    order[result[0]] = 0;
    for(auto i: v::iota(1, n)) {
      order[result[i]] = keys[result[i - 1]] == keys[result[i]] ? order[result[i - 1]] : i;
    }
  }

  return result;
}

/*
 * Oblicza tablicę sufiksową, czyli tablicę początków posortowanych
 * leksykograficznie sufiksów, przy użyciu haszowania w O(n log^2 n).
 * Ten algorytm jest wolniejszy od poprzedniego.
 */
template<int alpha_size>
vector<int> suffix_array_hash(string const& str, auto alpha_to_num) {
  int n = str.size();

  vector<int> result(n);
  iota(result.begin(), result.end(), 0);

  PrefixHashes<Z<(1ull << 62) - 57, true>, alpha_size, decltype(alpha_to_num)> hash(str, alpha_to_num);
  r::sort(result, [&](int a, int b) {
    auto max_common_prefix = min(n - a, n - b);
    auto left = 0, right = max_common_prefix;
    while(left < right) {
      auto mid = left + (right - left + 1) / 2;
      if(hash.get(a, a + mid - 1) == hash.get(b, b + mid - 1)) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    return left == max_common_prefix ? a > b : str[a + left] < str[b + left];
  });

  return result;
}
