/*
 * Szybkie I/O - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <cstdio>
#include <cctype>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

/*
 * Szybkie wczytywanie do zmiennej
 */
void read(char &c) {
  do {
    c = getchar_unlocked();
  } while(isspace(c));
}

void read(string &str) {
  while(true) {
    auto c = getchar_unlocked();
    if(!isspace(c)) {
      str.push_back(c);
    } else if(!str.empty()) break;
  }
}

template<class A, std::enable_if_t<std::is_integral_v<A>, int> = 123>
void read(A &num) {
  num = 0;
  auto is_start = true, is_neg = false;
  while(true) {
    auto c = getchar_unlocked();
    if(!isspace(c)) {
      if(c == '-' && !is_neg) {
        is_neg = true;
      } else {
        assert('0' <= c && c <= '9');
        num *= 10;
        num += c - '0';
        is_start = false;
      }
    } else if(!is_start) break;
  }
  if(is_neg) {
    num = -num;
  }
}

template<class A, class B>
void read(pair<A, B> &pair) {
  read(pair.first);
  read(pair.second);
}

template<class A>
void read(vector<A> &vec) {
  for(auto &i: vec) {
    read(i);
  }
}

/*
 * Szybkie wypisanie wartości
 */
int const fastio_out_size = 1'000'000;
int fastio_out_cnt = 0;
char fastio_out[fastio_out_size];

void fastio_flush() {
  fwrite(fastio_out, sizeof(char), fastio_out_cnt, stdout);
  fastio_out_cnt = 0;
}

void print(char c) {
  if(fastio_out_cnt >= fastio_out_size) {
    fastio_flush();
  }
  fastio_out[fastio_out_cnt++] = c;
}

void print(string const& str) {
  for(auto i: str) {
    print(i);
  }
}

template<class A, std::enable_if_t<std::is_integral_v<A>, int> = 123>
void print(A num) {
  if(num == 0) {
    print('0');
    return;
  }
  if(num < 0) {
    print('-');
    num = -num;
  }
  char rev[32];
  int cnt = 0;
  while(num > 0) {
    rev[cnt] = num % 10 + '0';
    num /= 10;
    cnt++;
  }
  for(int i = cnt - 1; i >= 0; i--) {
    print(rev[i]);
  }
}

void print(char const* str) {
  while(*str != '\0') {
    print(*str);
    str++;
  }
}

void print(bool val) {
  print(val ? "true" : "false");
}
