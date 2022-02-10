/*
 * Chińskie twierdzenie o resztach - digitcrusher/algorytmy
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
#include "compat/optional.hpp"
#include "math/diophantine.hpp"
#include "math/mod.hpp"
#include <vector>

/*
 * Chińskie twierdzenie o resztach - Rozwiązuje układy równań modularnych:
 *   x % mods[0] = rems[0]
 *   x % mods[1] = rems[1]
 *   …
 *   x % mods[n - 1] = rems[n - 1]
 */
struct CrtResult {
  ll soln, mod;
};
optional<CrtResult> crt(vector<ll> const& rems, vector<ll> const& mods) {
  assert(rems.size() == mods.size());

  ll mod1 = mods[0];
  assert(mod1 > 0);
  ll rem1 = norm_mod(rems[0], mod1);
  for(int i = 1; i < rems.size(); i++) {
    ll mod2 = mods[i];
    assert(mod2 > 0);
    ll rem2 = norm_mod(rems[i], mod2);

    auto soln = solve_lin_diophantine(mod1, mod2, rem2 - rem1);
    if(soln == nullopt) {
      return nullopt;
    }
    ll lcm = mod1 / soln->gcd_ab * mod2;
    assert(lcm > 0);
    rem1 = norm_mod(rem1 + soln->x % (lcm / mod1) * mod1, lcm);
    mod1 = lcm;
  }
  return CrtResult{rem1, mod1};
}
