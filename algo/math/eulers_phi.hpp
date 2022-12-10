/*
 * Funkcja φ Eulera - digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include <vector>

/*
 * Funkcja φ Eulera -
 *   Oblicza liczbę liczb w [1, x] wspólnie pierwszych z x na podstawie jego rozkładu
 *   na czynniki pierwsze w O(n), gdzie n to liczba dzielników pierwszych x.
 */
ll eulers_phi(ll x, vector<pair<ll, int>> const& factors) {
  ll result = x;
  for(auto i: factors) {
    result -= result / i.first;
  }
  return result;
}
