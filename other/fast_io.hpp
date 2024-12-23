/*
 * Szybkie I/O - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2024 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"

/*
 * Szybki drop-in zamiennik dla cin i cout.
 */
struct {
  auto& operator>>(char &c) {
    do {
      c = getchar_unlocked();
    } while(isspace(c));
    return *this;
  }

  auto& operator>>(string &str) {
    str.clear();
    while(true) {
      auto c = getchar_unlocked();
      if(!isspace(c)) {
        str.push_back(c);
      } else if(!str.empty()) break;
    }
    return *this;
  }

  auto& operator>>(std::integral auto &num) {
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
        }
        is_start = false;
      } else if(!is_start) break;
    }
    if(is_neg) {
      num = -num;
    }
    return *this;
  }

  auto& operator>>(pair<auto, auto> &pair) {
    return *this >> pair.first >> pair.second;
  }

  auto& operator>>(r::range auto &range) {
    for(auto &i: range) {
      *this >> i;
    }
    return *this;
  }

  char out[1'000'000];
  int out_cnt = 0;

  void flush() {
    fwrite(out, sizeof(char), out_cnt, stdout);
    out_cnt = 0;
  }

  auto& operator<<(char c) {
    if(out_cnt >= std::size(out)) {
      flush();
    }
    out[out_cnt++] = c;
    return *this;
  }

  auto& operator<<(string const& str) {
    for(auto i: str) {
      *this << i;
    }
    return *this;
  }

  auto& operator<<(std::integral auto num) {
    if(num == 0) {
      return *this << '0';
    }
    if(num < 0) {
      *this << '-';
      num = -num;
    }
    char rev[32];
    auto cnt = 0;
    while(num > 0) {
      rev[cnt] = num % 10 + '0';
      num /= 10;
      cnt++;
    }
    for(auto i = cnt - 1; i >= 0; i--) {
      *this << rev[i];
    }
    return *this;
  }

  auto& operator<<(char const* str) {
    while(*str != '\0') {
      *this << *str;
      str++;
    }
    return *this;
  }

  auto& operator<<(bool val) {
    return *this << (val ? "true" : "false");
  }
} fastio;
