/*
 * Funkcja φ Eulera - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"

/*
 * Funkcja φ Eulera -
 *   Oblicza liczbę liczb w [1, x] wspólnie pierwszych z x na podstawie jego rozkładu
 *   na czynniki pierwsze w O(n), gdzie n to liczba dzielników pierwszych x.
 */
ll eulers_phi(ll x, vector<pair<ll, int>> const& factors) {
  auto result = x;
  for(auto [prime, _]: factors) {
    result -= result / prime;
  }
  return result;
}
