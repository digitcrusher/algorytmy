/*
 * Algorytm Mo - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <cmath>

/*
 * Algorytm Mo -
 *   Metoda przechodzenia po zapytaniach o przedziały pozwalająca na
 *   odpowiedzenie na nie wszystkie w czasie O((n + q) * sqrt(n)), gdzie n to
 *   zakres wartości granic przedziałów. Ta implementacja steruje tylko
 *   przedziałem aktualnej odpowiedzi, a użytkownik sam jest odpowiedzialny za
 *   trzymanie i odpowiednie modyfikowanie jej.
 *
 * init: (int, int) -> void
 *   Inicjalizuje odpowiedź na dany przedział.
 * expand_left: void -> void
 *   Rozszerza lewą granicę odpowiedzi o jeden.
 * expand_right: void -> void
 *   Rozszerza prawą granicę odpowiedzi o jeden.
 * shrink_left: void -> void
 *   Kurczy lewą granicę odpowiedzi o jeden.
 * shrink_right: void -> void
 *   Kurczy prawą granicę odpowiedzi o jeden.
 * answer: int -> void
 *   Informuje, że odpowiedź jest gotowa dla danego zapytania.
 */
void mo(int n, vector<pair<int, int>> const& queries,
        auto init, auto expand_left, auto expand_right,
        auto shrink_left, auto shrink_right, auto answer)
{
  int q = queries.size();
  if(q == 0) return;

  vector<int> order(q);
  iota(order.begin(), order.end(), 0);
  auto sqrt_n = max<int>(1, sqrt(n));
  r::sort(order, {}, [&](int idx) {
    auto [l, r] = queries[idx];
    auto block = l / sqrt_n + (l < 0 ? -1 : 0);
    return tuple(block, block % 2 == 0 ? r : -r, l);
  });

  auto [l, r] = queries[order[0]];
  init(l, r);
  answer(order[0]);
  for(auto i: order | v::drop(1)) {
    auto [new_l, new_r] = queries[i];
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
    answer(i);
  }
}
