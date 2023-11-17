/*
 * Funkcja prefiksowa - digitcrusher/algorytmy
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
 * Funkcja prefiksowa -
 *   Oblicza dla każdego prefiksu długość jego
 *   najdłuższego prefikso-sufiksu w O(n).
 */
vector<int> prefix_func(string const& str) {
  int const n = str.size();

  vector<int> result(n + 1);
  result[0] = result[1] = 0;
  for(auto i: v::iota(2, n + 1)) {
    result[i] = result[i - 1];
    while(result[i] > 0 && str[i - 1] != str[result[i]]) {
      result[i] = result[result[i]];
    }
    if(str[i - 1] == str[result[i]]) {
      result[i]++;
    }
  }

  return result;
}
