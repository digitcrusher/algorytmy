/*
 * Chińskie twierdzenie o resztach - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/diophantine.hpp"
#include "math/mod.hpp"
#include <optional>
#include <vector>

/*
 * Chińskie twierdzenie o resztach -
 *   Rozwiązuje układy równań modularnych w O(n):
 *     x % mods[0] = rems[0]
 *     x % mods[1] = rems[1]
 *     …
 *     x % mods[n - 1] = rems[n - 1]
 */
struct CRT {
  ll soln, mod;
};
optional<CRT> crt(vector<ll> const& rems, vector<ll> const& mods) {
  assert(rems.size() == mods.size());

  auto mod1 = mods[0];
  assert(mod1 > 0);
  auto rem1 = norm_mod(rems[0], mod1);
  for(int i = 1; i < rems.size(); i++) {
    auto mod2 = mods[i];
    assert(mod2 > 0);
    auto rem2 = norm_mod(rems[i], mod2);

    auto soln = solve_lin_diophantine(mod1, mod2, rem2 - rem1);
    if(!soln) {
      return nullopt;
    }
    auto lcm = mod1 / soln->gcd_ab * mod2;
    assert(lcm > 0);
    rem1 += mod_mul(soln->x % (lcm / mod1), mod1, lcm);
    if(rem1 >= lcm) {
      rem1 -= lcm;
    }
    mod1 = lcm;
  }
  return CRT{rem1, mod1};
}
