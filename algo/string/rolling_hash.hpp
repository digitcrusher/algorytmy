/*
 * Haszowanie w okienku - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include "math/mod.hpp"
#include <queue>

/*
 * Haszowanie w okienku -
 *   Kolejka obsługująca operację obliczenia
 *   haszu wszystkich znaków (hash) w O(1).
 *
 * AlphaToNum: char -> int
 *   Przypisuje każdemu znakowi z alfabetu unikalną liczbę w [0, alpha_size).
 * NumToAlpha: int -> char
 *   Funkcja odwrotna do AlphaToNum
 */
template<class Z, int alpha_size, class AlphaToNum>
struct RollingHash {
  AlphaToNum alpha_to_num;

  Z hash = 0;
  queue<char> chars;

  RollingHash(AlphaToNum alpha_to_num = {}): alpha_to_num(alpha_to_num) {}

  char front() {
    return chars.front();
  }
  void push(char c) {
    hash = hash * (alpha_size + 1) + alpha_to_num(c) + 1;
    chars.push(c);
  }
  void pop() {
    hash -= Z(alpha_size + 1).pow(size() - 1) * (alpha_to_num(front()) + 1);
    chars.pop();
  }
  void clear() {
    hash = 0;
    decltype(chars)().swap(chars);
  }
  bool empty() {
    return chars.empty();
  }
  int size() {
    return chars.size();
  }
};
