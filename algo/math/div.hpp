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
#include "math/eulers_phi.hpp"
#include "math/factor.hpp"
#include "math/int.hpp"
#include "math/mod.hpp"
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
    result *= (fast_pow(prime, exp + 1) - 1) / (prime - 1);
  }
  return result;
}

/*
 * Oblicza iloczyn dodatnich dzielników liczby przy pomocy jej rozkładu na
 * czynniki pierwsze w O(n), gdzie n to liczba dzielników pierwszych tej
 * liczby.
 */
ll div_product(vector<pair<ll, int>> const& factors, ll mod) {
  ll result = 1, divc = 1;
  auto totient = eulers_phi(mod, factor_pollard_rho(mod));
  for(auto [prime, exp]: factors) {
    result = mod_mul(mod_pow(result, exp + 1, mod), mod_pow(prime, mod_mul(exp * (exp + 1) / 2, divc, totient), mod), mod);
    divc = mod_mul(divc, exp + 1, totient);
  }
  return result;
}
