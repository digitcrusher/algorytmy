/*
 * Najmniejsze przesunięcie cykliczne - digitcrusher/algorytmy
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
 * Algorytm Bootha -
 *   Znajduje najmniejsze przesunięcie cykliczne przy użyciu KMP w O(n).
 */
int min_rot(string str) {
  int const n = str.size();

  int result = 0;

  str += str;
  vector<int> kmp(2 * n);
  kmp[0] = kmp[1] = 0;
  int matchedc = 0;
  for(int i = 1; i - matchedc < n && matchedc + 1 < n; i++) {
    while(matchedc > 0 && str[i] != str[result + matchedc]) {
      if(str[i] < str[result + matchedc]) {
        result = i - matchedc;
      }
      matchedc = kmp[matchedc];
    }
    if(str[i] == str[result + matchedc]) {
      matchedc++;
    } else if(str[i] < str[result]) {
      result = i;
    }
    kmp[i - result + 1] = matchedc;
  }

  return result;
}
