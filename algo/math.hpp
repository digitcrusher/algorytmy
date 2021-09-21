/*
 * Algorytmy matematyczne - digitcrusher/algorytmy
 *
 * Copyright (c) 2021 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once
#include "common.hpp"
#include "compat/optional.hpp"
#include <cmath>
#include <stdexcept>
#include <vector>

// TODO: https://stackoverflow.com/questions/68772236/what-is-the-difference-between-std-gcd-and-stdgcd
// TODO: floor_div i ceil_div
// TODO: poorganizuj kodzik

/*
 * Znajduje gotowe funkcje NWD i NWW lub definiuje własną implementację.
 */
#if __cplusplus < 201402L
# if defined(__GLIBCXX__) || defined(__GLIBCPP__)
#   include <bits/stl_algo.h>
namespace std {
  ll gcd(ll a, ll b) {
    return std::__gcd(a, b);
  }
}
# else
namespace std {
  ll gcd(ll a, ll b) {
    if(b == 0) {
      return a;
    }
    return gcd(b, a % b);
  }
}
# endif

namespace std {
  ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
  }
}

#elif __cplusplus < 201703L
# include <experimental/numeric>
namespace std {
  using experimental::gcd;
  using experimental::lcm;
}

#else
# include <numeric>
#endif


struct ExtEuclidResult {
  ll gcd;
  ll x, y;
  ll a, b;

  /*
   * Zwraca kolejne współczynniki Bézouta dla a i b.
   */
  ExtEuclidResult shift_coefs(int step) {
    if(gcd == 0) {
      throw std::runtime_error(
        "Dla NWD równego zero istnieje nieskończenie wiele współczynników."
      );
    }
    return {
      gcd,
      x + b / gcd * step,
      y - a / gcd * step,
      a, b
    };
  }
};
ExtEuclidResult internal_ext_euclid(ll a, ll b) {
  if(b == 0) {
    return {a, 1, 0, a, b};
  }
  auto sub = internal_ext_euclid(b, a % b);
  return {
    sub.gcd,
    sub.y,
    sub.x - a / b * sub.y,
    a, b
  };
}
/*
 * Rozszerzony algorytm Euklidesa -
 *   Znajduje nwd oraz współczynniki Bézouta liczb a i b,
 *   czyli jedno z rozwiązań dla równania diofantycznego ax + by = NWD(a, b)
 *   i, co za tym idzie, wszystkie rozwiązania.
 */
ExtEuclidResult ext_euclid(ll a, ll b) {
  auto result = internal_ext_euclid(abs(a), abs(b));
  if(a < 0) {
    result.x = -result.x;
  }
  if(b < 0) {
    result.y = -result.y;
  }
  return result;
}



struct LinDiophantineSoln {
  ll x, y;
  ll a, b;
  ll gcd_ab;

  /*
   * Zwraca kolejne rozwiązanie równania diofantycznego.
   */
  LinDiophantineSoln shift_soln(int step) {
    return {
      x + b / gcd_ab * step,
      y - a / gcd_ab * step,
      a, b,
      gcd_ab
    };
  }
};
/*
 * Znajduje rozwiązanie równania diofantycznego ax + by = c
 * i, co za tym idzie, wszystkie rozwiązania.
 */
optional<LinDiophantineSoln> solve_lin_diophantine(ll a, ll b, ll c) {
  auto gcd = ext_euclid(a, b);
  if(c % gcd.gcd != 0) {
    return nullopt;
  }
  return LinDiophantineSoln{
    c / gcd.gcd * gcd.x,
    c / gcd.gcd * gcd.y,
    a, b,
    gcd.gcd,
  };
}



/*
 * Normalizuje a do przedziału [0, mod) z zachowaniem a' = a % mod.
 */
ll norm_mod(ll a, ll mod) {
  ll x = a % mod;
  return x + (x < 0 ? mod : 0);
}



/*
 * Iteratywne mnożenie i potęgowanie modularne
 */
ll mod_mul(ll a, ll b, ll mod) {
  ll result = 0;
  if(b < 0) {
    a = -a;
    b = -b;
  }
  while(b > 0) {
    if(b % 2 == 1) {
      result = (result + a) % mod;
    }
    a = a * 2 % mod;
    b /= 2;
  }
  return result;
}
ll mod_pow(ll a, ll b, ll mod) {
  assert(b >= 0);
  ll result = 1;
  while(b > 0) {
    if(b % 2 == 1) {
      result = result * a % mod;
    }
    a = a * a % mod;
    b /= 2;
  }
  return result;
}



/*
 * Odwrotność modularna - a * mod_inv(a, m) = 1 (mod m)
 */
optional<ll> mod_inv_ext_euclid(ll a, ll mod) {
  auto gcd = ext_euclid(a, mod);
  if(gcd.gcd != 1) {
    return nullopt;
  }
  return norm_mod(gcd.x, mod);
}
optional<ll> mod_inv(ll a, ll mod) {
  return mod_inv_ext_euclid(a, mod);
}



/*
 * Odwrotność modularna dla dzielników będących liczbami pierwszymi
 */
ll mod_inv_prime(ll a, ll prime_mod) {
  return mod_pow(a, prime_mod - 2, prime_mod); // z małego twierdzenia Fermata
}



/*
 * Chińskie twierdzenie o resztach - Rozwiązuje układy równań modularnych:
 *   x = rems[0] (mod mods[0])
 *   x = rems[1] (mod mods[1])
 *   …
 *   x = rems[n - 1] (mod mods[n - 1])
 */
struct CrtResult {
  ll soln, mod;
};
optional<CrtResult> crt(vector<ll> const& rems, vector<ll> const& mods) {
  assert(rems.size() == mods.size());

  ll mod1 = mods.front();
  assert(mod1 > 0);
  ll rem1 = norm_mod(rems.front(), mod1);
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
