/*
 * Pierwiastek pierwotny - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/eulers_phi.hpp"
#include "math/factor.hpp"
#include "math/mod.hpp"

/*
 * Pierwiastek pierwotny -
 *   Znajduje najmniejsze x takie, że dla każdej liczby wspólnie pierwszej z mod
 *   istnieje potęga x przystająca do niej, w O(log^6 mod log phi(mod) log mod).
 */
optional<ll> primitive_root(ll mod) {
  assert(mod > 0);
  if(mod == 1) {
    return 0;
  } else if(mod == 2) {
    return 1;
  } else if(mod == 4) {
    return 3;
  }

  auto mod_factors = factor_pollard_rho(mod);
  if(mod_factors.size() > 2 ||
     (mod_factors.size() == 1 && mod_factors[0].first == 2) ||
     (mod_factors.size() == 2 && r::count(mod_factors, pair(2ll, 1)) == 0)) {
    return nullopt;
  }

  auto totient = eulers_phi(mod, mod_factors);
  auto totient_factors = factor_pollard_rho(totient);
  return *r::find_if(v::iota(2ll, mod), [&](ll root) {
    return r::none_of(mod_factors, λ(root % _.first == 0)) &&
           r::none_of(totient_factors, λ(mod_pow(root, totient / _.first, mod) == 1));
  });
}
