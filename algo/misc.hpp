/*
 * Różne rzeczy - digitcrusher/algorytmy
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

template<bool cond, class A, class B>
struct type_if {};

template<class A, class B>
struct type_if<true, A, B> {
  using type = A;
};

template<class A, class B>
struct type_if<false, A, B> {
  using type = B;
};

template<bool cond, class A, class B>
using type_if_t = typename type_if<cond, A, B>::type;



#include <iterator>
#include <type_traits>

template<class InputIt>
using require_input_iter =
  typename std::enable_if<
    std::is_convertible<
      typename std::iterator_traits<InputIt>::iterator_category,
      std::input_iterator_tag
    >::value
  >::type;



#include <vector>
#include <utility>

namespace std {
  template<class A, class B>
  struct hash<pair<A, B>> {
    size_t operator()(pair<A, B> const& pair) const {
      size_t a = hash<A>()(pair.first), b = hash<B>()(pair.second);
      // Formuła zapożyczona z biblioteki Boost
      return a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2));
    }
  };

  template<class A>
  struct hash<vector<A>> {
    size_t operator()(vector<A> const& vec) const {
      if(vec.empty()) {
        return 0;
      }
      size_t result = hash<A>()(vec[0]);
      for(int i = 1; i < vec.size(); i++) {
        // Formuła zapożyczona z biblioteki Boost
        result ^= hash<A>()(vec[i]) + 0x9e3779b9 + (result << 6) + (result >> 2);
      }
      return result;
    }
  };
}



#include <cmath>

ld const pi = acosl(-1);



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



#include <sys/resource.h>

/*
 * Może się przydać przy lokalnym testowaniu rozwiązania na dużych
 * danych. Na sprawdzaczkach jest niepotrzebne i najpewniej wywali błąd.
 */
void set_stack_size(ll megabytes) {
  rlimit rl;
  rl.rlim_cur = (rlim_t) megabytes * 1000 * 1000;
  setrlimit(RLIMIT_STACK, &rl);
}
