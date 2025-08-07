/*
 * Wypisywanie i wczytywanie rzeczy ze standardowej biblioteki
 *                                      digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2025 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <complex>
#include <iostream>

ostream& operator<<(ostream &stream, complex<auto> const& num) {
  if(num.real() != 0 || num.imag() == 0) {
    stream << num.real();
  }
  if(num.imag() != 0) {
    if(num.real() != 0) {
      stream << (num.imag() >= 0 ? "+" : "-") << abs(num.imag());
    } else {
      stream << num.imag();
    }
    stream << "i";
  }
  return stream;
}
template<class A>
istream& operator>>(istream &stream, complex<A> &num) {
  A part;
  char sign;
  stream >> part;
  if(stream.peek() == 'i') {
    num.imag(part);
    num.real(0);
    stream >> sign;
  } else {
    num.real(part);
    if(stream.peek() == '+' || stream.peek() == '-') {
      stream >> sign >> part;
      num.imag(sign == '+' ? part : -part);
      stream >> sign;
    }
  }
  return stream;
}

ostream& operator<<(ostream &stream, pair<auto, auto> const& pair) {
  return stream << pair.first << " " << pair.second;
}
istream& operator>>(istream &stream, pair<auto, auto> &pair) {
  return stream >> pair.first >> pair.second;
}

template<class... A>
ostream& operator<<(ostream &stream, tuple<A...> const& tuple) {
  std::apply([&](A const&... elems) {
    auto i = 0;
    ((stream << (i++ > 0 ? " " : "") << elems), ...);
  }, tuple);
  return stream;
}
template<class... A>
istream& operator>>(istream &stream, tuple<A...> &tuple) {
  std::apply([&](A &...elems) {
    (stream >> ... >> elems);
  }, tuple);
  return stream;
}

template<class A>
constexpr auto is_already_printable = std::is_convertible_v<A, char const*>;
template<>
constexpr auto is_already_printable<string> = true;
template<>
constexpr auto is_already_printable<string_view> = true;

template<class A>
constexpr auto printability = std::is_arithmetic_v<A> ? 1 : 0;
template<class A>
constexpr auto printability<complex<A>> = 1;
template<>
constexpr auto printability<char> = 2;

template<r::range R> requires (!is_already_printable<R>)
ostream& operator<<(ostream &stream, R const& range) {
  switch(printability<r::range_value_t<R>>) {
  case 0:
    for(auto const& i: range) {
      stream << i << "\n";
    }
    break;

  case 1: {
    auto it = begin(range);
    if(it != end(range)) {
      stream << *it++;
      while(it != end(range)) {
        stream << " " << *it++;
      }
    }
  } break;

  case 2:
    for(auto const& i: range) {
      stream << i;
    }
    break;
  }

  return stream;
}
template<r::range R> requires (!std::is_same_v<R, string>)
istream& operator>>(istream &stream, R &range) {
  for(auto &i: range) {
    stream >> i;
  }
  return stream;
}
