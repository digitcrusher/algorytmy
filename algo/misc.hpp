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
#include <iterator>
#include <type_traits>

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



template<class InputIt>
using require_input_iter =
  typename std::enable_if<
    std::is_convertible<
      typename std::iterator_traits<InputIt>::iterator_category,
      std::input_iterator_tag
    >::value
  >::type;



namespace std {
  template<class A, class B>
  struct hash<pair<A, B>> {
    size_t operator()(pair<A, B> const& pair) const {
      size_t a = hash<A>()(pair.first), b = hash<B>()(pair.second);
      // Formuła zapożyczona z biblioteki Boost
      return a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2));
    }
  };
}
