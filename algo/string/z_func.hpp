/*
 * Funkcja Z - digitcrusher/algorytmy
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
 * Funkcja Z -
 *   Oblicza dla każdego sufiksu długość jego najdłuższego
 *   wspólnego prefiksu z całym ciągiem w O(n).
 */
vector<int> z_func(string const& str) {
  int const n = str.size();

  vector<int> result(n);
  result[0] = n;
  for(int i = 1, l = 0, r = 0; i < n; i++) {
    result[i] = i < r ? min(r - i, result[i - l]) : 0;
    while(i + result[i] < n && str[i + result[i]] == str[result[i]]) {
      result[i]++;
    }
    if(r < i + result[i]) {
      l = i;
      r = i + result[i];
    }
  }

  return result;
}