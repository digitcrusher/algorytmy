/*
 * Hasze prefiksowe - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
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
 *   Struktura danych wspierająca operację obliczenia
 *   haszu spójnego podciągu znaków (get) w O(1).
 *
 * AlphaToNum: char -> int
 *   Przypisuje każdemu znakowi z alfabetu unikalną liczbę w [0, alpha_size).
 * NumToAlpha: int -> char
 *   Funkcja odwrotna do AlphaToNum
 */
template<int alpha_size, class AlphaToNum>
struct PrefixHashes {
  AlphaToNum alpha_to_num;

  ll mod;
  vector<ll> hashes;

  PrefixHashes(string const& str, ll mod, AlphaToNum alpha_to_num = {}):
    mod(mod), hashes(str.size() + 1), alpha_to_num(alpha_to_num)
  {
    if(str.empty()) return;
    hashes[0] = 0;
    for(auto i: v::iota(1, (int) str.size() + 1)) {
      hashes[i] = norm_mod(mod_mul(hashes[i - 1], alpha_size + 1, mod) + alpha_to_num(str[i - 1]) + 1, mod);
    }
  }

  ll get(int l, int r) {
    assert(l <= r);
    auto result = hashes[r + 1] - mod_mul(hashes[l], mod_pow(alpha_size + 1, r - l + 1, mod), mod);
    if(result < 0) {
      result += mod;
    }
    return result;
  }
};
