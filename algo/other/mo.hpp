/*
 * Algorytm Mo - digitcrusher/algorytmy
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
#include <cmath>
#include <numeric>
#include <vector>

/*
 * Algorytm Mo -
 *   Metoda przechodzenia po zapytaniach o przedziały pozwalająca na
 *   odpowiedzenie na nie wszystkie w czasie O((n + q) * sqrt(n)), gdzie n to
 *   zakres wartości granic przedziałów. Ta implementacja steruje tylko
 *   przedziałem aktualnej odpowiedzi, a użytkownik sam jest odpowiedzialny za
 *   trzymanie i odpowiednie modyfikowanie jej.
 *
 * Init: (int, int) -> void
 *   Inicjalizuje odpowiedź na dany przedział.
 *
 * ExpandLeft: void -> void
 *   Rozszerza lewą granicę odpowiedzi o jeden.
 *
 * ExpandRight: void -> void
 *   Rozszerza prawą granicę odpowiedzi o jeden.
 *
 * ShrinkLeft: void -> void
 *   Kurczy lewą granicę odpowiedzi o jeden.
 *
 * ShrinkRight: void -> void
 *   Kurczy prawą granicę odpowiedzi o jeden.
 *
 * Answer: int -> void
 *   Informuje, że odpowiedź jest gotowa dla danego zapytania.
 */
template<
  class Init,
  class ExpandLeft,
  class ExpandRight,
  class ShrinkLeft,
  class ShrinkRight,
  class Answer
> void mo(int n, vector<pair<int, int>> const& queries, Init init,
          ExpandLeft expand_left, ExpandRight expand_right,
          ShrinkLeft shrink_left, ShrinkRight shrink_right, Answer answer)
{
  int const q = queries.size();
  if(q == 0) return;

  vector<int> order(q);
  iota(order.begin(), order.end(), 0);
  int sqrt_n = max<int>(1, sqrt(n));
  auto key = [&](pair<int, int> query) {
    auto [l, r] = query;
    int block = l / sqrt_n + (l < 0 ? -1 : 0);
    return tuple(block, block % 2 == 0 ? r : -r, l);
  };
  sort(order.begin(), order.end(), [&](int a, int b) {
    return key(queries[a]) < key(queries[b]);
  });

  auto [l, r] = queries[order[0]];
  init(l, r);
  answer(order[0]);
  for(int i = 1; i < q; i++) {
    auto [new_l, new_r] = queries[order[i]];
    while(new_l < l) {
      expand_left();
      l--;
    }
    while(r < new_r) {
      expand_right();
      r++;
    }
    while(l < new_l) {
      shrink_left();
      l++;
    }
    while(new_r < r) {
      shrink_right();
      r--;
    }
    answer(order[i]);
  }
}
