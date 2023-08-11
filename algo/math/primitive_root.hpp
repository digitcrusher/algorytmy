/*
 * Pierwiastek pierwotny - digitcrusher/algorytmy
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
#include "math/mod.hpp"
#include <optional>

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
  pair const two = {2ll, 1};
  if(mod_factors.size() > 2 ||
     (mod_factors.size() == 1 && mod_factors[0].first == 2) ||
     (mod_factors.size() == 2 && mod_factors[0] != two && mod_factors[1] != two)) {
    return nullopt;
  }

  auto totient = eulers_phi(mod, mod_factors);
  auto totient_factors = factor_pollard_rho(totient);
  for(ll root = 2; root < mod; root++) {
    auto is_good = true;
    for(auto [prime, _]: mod_factors) {
      if(root % prime == 0) {
        is_good = false;
        break;
      }
    }
    if(!is_good) continue;
    for(auto [prime, _]: totient_factors) {
      if(mod_pow(root, totient / prime, mod) == 1) {
        is_good = false;
        break;
      }
    }
    if(is_good) {
      return root;
    }
  }
  assert(false);
}
