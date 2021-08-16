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
#include <cmath>
#include <vector>

// TODO: https://stackoverflow.com/questions/68772236/what-is-the-difference-between-std-gcd-and-stdgcd

/*
 * Znajduje gotowe funkcje nwd i nww lub definiuje własną implementację.
 */
#if __cplusplus >= 201402L
# include <experimental/numeric>
using std::experimental::gcd;
using std::experimental::lcm;

#else
# if defined(__GLIBCXX__) || defined(__GLIBCPP__)
#   include <bits/stl_algo.h>
ll gcd(ll a, ll b) {
  return std::__gcd(a, b);
}
# else
ll gcd(ll a, ll b) {
  if(b == 0) {
    return a;
  }
  return gcd(b, a % b);
}
# endif

ll lcm(ll a, ll b) {
  return a / gcd(a, b) * b;
}
#endif



struct ExtEuclidResult {
  ll div;
  ll x, y;
  ll a, b;

  /*
   * Zwraca kolejne współczynniki Bézouta dla a i b.
   */
  ExtEuclidResult shift_coefs(int step) {
    if(div == 0) {
      throw std::runtime_error(
        "Dla nwd równego zero istnieje nieskończenie wiele współczynników."
      );
    }
    return {
      div,
      x + b / div * step,
      y - a / div * step,
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
    sub.div,
    sub.y,
    sub.x - a / b * sub.y,
    a, b
  };
}
/*
 * Rozszerzony algorytm Euklidesa -
 *   Znajduje nwd oraz współczynniki Bézouta liczb a i b,
 *   czyli jedno z rozwiązań dla równania diofantycznego ax + by = nwd(a, b).
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
 * Rozwiązuje równanie diofantyczne ax + by = c.
 */
LinDiophantineSoln solve_lin_diophantine(ll a, ll b, ll c) {
  auto gcd = ext_euclid(a, b);
  if(c % gcd.div != 0) {
    throw std::runtime_error(
      "Nie ma rozwiązań równania diofantycznego ax + by = c, "
      "gdy c nie jest podzielne przez nwd(a, b)."
    );
  }
  ll x = c / gcd.div * gcd.x;
  ll y = c / gcd.div * gcd.y;
  return {
    a < 0 ? -x : x,
    b < 0 ? -y : y,
    a, b,
    gcd.div,
  };
}



/*
 * Normalizuje a do przedziału [0, mod) z zachowaniem a' = a (% mod).
 */
ll norm_mod(ll a, ll mod) {
  ll x = a % mod;
  return x + (x < 0 ? mod : 0);
}



/*
 * Bezpieczne iteratywne mnożenie i potęgowanie modularne
 */
ll mod_mul(ll a, ll b, ll mod) {
  ll result = 0;
  if(b < 0) {
    a = -a;
  }
  while(b != 0) {
    if(b % 2 != 0) {
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
ll mod_inv_ext_euclid(ll a, ll mod) {
  auto gcd = ext_euclid(a, mod);
  if(gcd.div != 1) {
    throw std::runtime_error(
      "Odwrotność modularna nie istnieje, "
      "gdy liczba i dzielnik są wspólnie pierwsze."
    );
  }
  return norm_mod(gcd.x, mod);
}
ll mod_inv(ll a, ll mod) {
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
CrtResult crt(std::vector<ll> const& rems, std::vector<ll> const& mods) {
  assert(rems.size() == mods.size());

  ll mod1 = mods.front();
  assert(mod1 > 0);
  ll rem1 = norm_mod(rems.front(), mod1);
  for(size_t i = 1; i < rems.size(); i++) {
    ll mod2 = mods[i];
    assert(mod2 > 0);
    ll rem2 = norm_mod(rems[i], mod2);

    LinDiophantineSoln soln;
    try {
      soln = solve_lin_diophantine(mod1, mod2, rem2 - rem1);
    } catch(std::runtime_error &e) {
      throw std::runtime_error(
        "Nie ma rozwiązań dla tego układu równań modularnych."
      );
    }
    ll lcm = mod1 / soln.gcd_ab * mod2;
    assert(lcm > 0);
    rem1 = norm_mod(rem1 + soln.x % (lcm / mod1) * mod1, lcm);
    mod1 = lcm;
  }
  return {rem1, mod1};
}
