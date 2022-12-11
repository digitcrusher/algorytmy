/*
 * Hasze prefiksowe - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/mod.hpp"
#include <string>
#include <vector>

/*
 * Hasze prefiksowe -
 *   Struktura danych wspierająca operację obliczenia haszu
 *   spójnego podciągu znaków (get) w O(1). Zużywa O(n) pamięci.
 *
 * AlphaToNum: char -> int
 *   Przypisuje każdemu znakowi z alfabetu unikalną liczbę w [0, alpha_size).
 * NumToAlpha: int -> char
 *   Funkcja odwrotna do AlphaToNum.
 */
template<int alpha_size, class AlphaToNum>
struct PrefixHashes {
  AlphaToNum alpha_to_num;

  ll mod;
  vector<ll> pref_hash;

  PrefixHashes(string const& str, ll mod, AlphaToNum alpha_to_num = AlphaToNum()):
    mod(mod), pref_hash(str.size()), alpha_to_num(alpha_to_num)
  {
    if(str.empty()) return;
    pref_hash[0] = (alpha_to_num(str[0]) + 1) % mod;
    for(int i = 1; i < str.size(); i++) {
      pref_hash[i] = mod_mul(pref_hash[i - 1], alpha_size + 1, mod) + alpha_to_num(str[i]) + 1;
      pref_hash[i] %= mod;
    }
  }

  ll get(int l, int r) {
    assert(l <= r);
    if(l == 0) {
      return pref_hash[r];
    } else {
      return norm_mod(pref_hash[r] - mod_mul(pref_hash[l - 1], mod_pow(alpha_size + 1, r - l + 1, mod), mod), mod);
    }
  }
};
