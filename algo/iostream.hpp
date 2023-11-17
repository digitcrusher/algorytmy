/*
 * Wypisywanie i wczytywanie rzeczy ze standardowej biblioteki
 *                                      digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2023 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once
#include "common.hpp"
#include <complex>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

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
  A real;
  stream >> real;
  if(stream.peek() == 'i') {
    num.imag(real);
  } else {
    num.real(real);
    if(stream.peek() == '+' || stream.peek() == '-') {
      char sign;
      A imag;
      stream >> sign >> imag;
      num.imag(sign == '+' ? imag : -imag);
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
    int i = 0;
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

template<class A> requires std::is_arithmetic_v<A>
ostream& operator<<(ostream &stream, vector<A> const& vec) {
  if(!vec.empty()) {
    stream << vec[0];
    for(auto const& i: vec | v::drop(1)) {
      stream << " " << i;
    }
  }
  return stream;
}
template<class A> requires (!std::is_arithmetic_v<A>)
ostream& operator<<(ostream &stream, vector<A> const& vec) {
  for(auto const& i: vec) {
    stream << i << "\n";
  }
  return stream;
}
ostream& operator<<(ostream &stream, vector<complex<auto>> const& vec) {
  if(!vec.empty()) {
    stream << vec[0];
    for(auto const& i: vec | v::drop(1)) {
      stream << " " << i;
    }
  }
  return stream;
}
istream& operator>>(istream &stream, vector<auto> &vec) {
  for(auto &i: vec) {
    stream >> i;
  }
  return stream;
}

template<class A>
constexpr auto enable_joined_print = false;
template<>
constexpr auto enable_joined_print<char> = true;

template<class A>
constexpr auto enable_compact_print = false;
template<class A> requires std::is_arithmetic_v<A>
constexpr auto enable_compact_print<A> = true;
template<class A>
constexpr auto enable_compact_print<complex<A>> = true;

template<r::view V> requires enable_joined_print<r::range_value_t<V>>
ostream& operator<<(ostream &stream, V view) {
  for(auto const& i: view) {
    stream << i;
  }
  return stream;
}
template<r::view V> requires (!enable_joined_print<r::range_value_t<V>> && enable_compact_print<r::range_value_t<V>>)
ostream& operator<<(ostream &stream, V view) {
  auto it = begin(view);
  if(it != end(view)) {
    stream << *it++;
    while(it != end(view)) {
      stream << " " << *it++;
    }
  }
  return stream;
}
template<r::view V> requires (!enable_joined_print<r::range_value_t<V>> && !enable_compact_print<r::range_value_t<V>>)
ostream& operator<<(ostream &stream, V view) {
  for(auto const& i: view) {
    stream << i << "\n";
  }
  return stream;
}
template<r::view V> requires is_lvalue_reference_v<r::range_value_t<V>>
istream& operator>>(istream &stream, V view) {
  for(auto &i: view) {
    stream >> i;
  }
  return stream;
}
