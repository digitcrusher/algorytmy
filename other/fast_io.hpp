/*
 * Szybkie I/O - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
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
void read(char &result) {
  do {
    result = getchar_unlocked();
  } while(isspace(result));
}

void read(string &result) {
  while(true) {
    char c = getchar_unlocked();
    if(!isspace(c)) {
      result.push_back(c);
    } else if(!result.empty()) break;
  }
}

template<class A, class = typename std::enable_if<std::is_integral<A>::value>::type>
void read(A &result) {
  result = 0;
  bool is_start = true;
  bool is_neg = false;
  while(true) {
    char c = getchar_unlocked();
    if(!isspace(c)) {
      if(c == '-' && !is_neg) {
        is_neg = true;
      } else {
        assert('0' <= c && c <= '9');
        result *= 10;
        result += c - '0';
        is_start = false;
      }
    } else if(!is_start) break;
  }
  if(is_neg) {
    result = -result;
  }
}

template<class A, class B>
void read(pair<A, B> &result) {
  read(result.first);
  read(result.second);
}

template<class A>
void read(vector<A> &result) {
  for(A &elem: result) {
    read(elem);
  }
}

/*
 * Szybkie wypisanie wartości
 */
int const fastio_out_size = 1000000;
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
  for(char c: str) {
    print(c);
  }
}

template<class A, class = typename std::enable_if<std::is_integral<A>::value>::type>
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
