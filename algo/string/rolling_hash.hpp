/*
 * Haszowanie w okienku - digitcrusher/algorytmy
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
#include "math/mod.hpp"
#include <queue>

/*
 * Haszowanie w okienku -
 *   Kolejka obsługująca operację obliczenia haszu
 *   wszystkich znaków (hash) w O(1). Zużywa O(n) pamięci.
 *
 * AlphaToNum: char -> int
 *   Przypisuje każdemu znakowi z alfabetu unikalną liczbę w [0, alpha_size).
 * NumToAlpha: int -> char
 *   Funkcja odwrotna do AlphaToNum.
 */
template<int alpha_size, class AlphaToNum>
struct RollingHash {
  AlphaToNum alpha_to_num;

  ll mod, hash = 0;
  queue<char> chars;

  RollingHash(ll mod, AlphaToNum alpha_to_num = AlphaToNum()):
    mod(mod), alpha_to_num(alpha_to_num) {}

  char front() {
    return chars.front();
  }
  void push(char c) {
    hash = mod_mul(hash, alpha_size + 1, mod) + alpha_to_num(c) + 1;
    hash %= mod;
    chars.push(c);
  }
  void pop() {
    hash -= mod_mul(alpha_to_num(front()) + 1, mod_pow(alpha_size + 1, size() - 1, mod), mod);
    hash = norm_mod(hash, mod);
    chars.pop();
  }
  void clear() {
    hash = 0;
    queue<char>().swap(chars);
  }
  bool empty() {
    return chars.empty();
  }
  int size() {
    return chars.size();
  }
};
