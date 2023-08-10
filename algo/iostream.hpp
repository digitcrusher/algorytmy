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

template<class A>
ostream& operator<<(ostream &stream, complex<A> const& num) {
  if(num.real() != 0 || num.imag() == 0) {
    stream << num.real();
  }
  if(num.imag() != 0) {
    if(num.real() != 0) {
      stream << (num.imag() > 0 ? "+" : "-");
      stream << abs(num.imag());
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
      if(sign == '+') {
        num.imag(imag);
      } else {
        num.imag(-imag);
      }
      stream >> sign;
    }
  }
  return stream;
}

template<class A, class B>
ostream& operator<<(ostream &stream, pair<A, B> const& pair) {
  return stream << pair.first << " " << pair.second;
}
template<class A, class B>
istream& operator>>(istream &stream, pair<A, B> &pair) {
  return stream >> pair.first >> pair.second;
}

template<class... A>
ostream& operator<<(ostream &stream, tuple<A...> const& tuple) {
  apply([&](A const&... elems) {
    int i = 0;
    ((stream << (i++ > 0 ? " " : "") << elems), ...);
  }, tuple);
  return stream;
}
template<class... A>
istream& operator>>(istream &stream, tuple<A...> &tuple) {
  apply([&](A &...elems) {
    (stream >> ... >> elems);
  }, tuple);
  return stream;
}

template<class A>
ostream& operator<<(ostream &stream, vector<A> const& vec) {
  if(!vec.empty()) {
    stream << vec[0];
    for(int i = 1; i < vec.size(); i++) {
      stream << " " << vec[i];
    }
  }
  return stream;
}
template<class A>
istream& operator>>(istream &stream, vector<A> &vec) {
  for(auto &i: vec) {
    stream >> i;
  }
  return stream;
}
