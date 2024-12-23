/*
 * Hasze prefiksowe - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/mod.hpp"

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
template<class Z, int alpha_size, class AlphaToNum>
struct PrefixHashes {
  AlphaToNum alpha_to_num;

  vector<Z> hashes;

  PrefixHashes(string const& str, AlphaToNum alpha_to_num = {}):
    hashes(str.size() + 1), alpha_to_num(alpha_to_num)
  {
    if(str.empty()) return;
    hashes[0] = 0;
    for(auto i: v::iota(1, (int) str.size() + 1)) {
      hashes[i] = hashes[i - 1] * (alpha_size + 1) + alpha_to_num(str[i - 1]) + 1;
    }
  }

  Z get(int l, int r) const {
    assert(l <= r);
    return hashes[r + 1] - hashes[l] * Z(alpha_size + 1).pow(r - l + 1);
  }
};
