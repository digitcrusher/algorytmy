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
#include <unordered_set>
#include <vector>

/*
 * Funkcja φ Eulera -
 *   Oblicza liczbę liczb w [1, n] wspólnie pierwszych z n na podstawie jego rozkładu
 *   na czynniki pierwsze w O(m), gdzie m to liczba dzielników pierwszych n.
 */
ll eulers_phi(ll n, vector<ll> const& factors) {
  ll result = n;
  unordered_set<ll> primes;
  for(ll i: factors) {
    if(primes.count(i) == 0) {
      result -= result / i;
      primes.insert(i);
    }
  }
  return result;
}
