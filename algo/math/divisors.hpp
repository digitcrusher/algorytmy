/*
 * Liczba, suma i iloczyn dzielników - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/int.hpp"
#include <vector>

/*
 * Oblicza liczbę dodatnich dzielników liczby na podstawie jej rozkładu na
 * czynniki pierwsze w O(n), gdzie n to liczba dzielników pierwszych tej
 * liczby.
 */
ll divc(vector<pair<ll, int>> const& factors) {
  ll result = 1;
  for(auto [_, exp]: factors) {
    result *= exp + 1;
  }
  return result;
}

/*
 * Oblicza sumę dodatnich dzielników liczby przy pomocy jej rozkładu na czynniki
 * pierwsze w O(n), gdzie n to liczba dzielników pierwszych tej liczby.
 */
ll div_sum(vector<pair<ll, int>> const& factors) {
  ll result = 1;
  for(auto [prime, exp]: factors) {
    result *= (pow(prime, exp + 1) - 1) / (prime - 1);
  }
  return result;
}

/*
 * Oblicza iloczyn dodatnich dzielników liczby przy pomocy jej rozkładu na
 * czynniki pierwsze w O(n), gdzie n to liczba dzielników pierwszych tej
 * liczby.
 */
ll div_product(vector<pair<ll, int>> const& factors) {
  ll result = 1, divc = 1;
  for(auto [prime, exp]: factors) {
    result *= pow(result, exp) * pow(prime, exp * (exp + 1) / 2 * divc);
    divc *= exp + 1;
  }
  return result;
}
