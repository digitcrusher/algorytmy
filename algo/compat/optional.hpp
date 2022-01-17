/*
 * Kompatybilnościowa implementacja <optional> z C++17 - digitcrusher/algorytmy
 *
 * Copyright (c) 2021-2022 Karol Łacina aka digitcrusher
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved. This software is offered as-is,
 * without any warranty.
 */
#pragma once

#if __cplusplus < 201402L
namespace std {
  struct nullopt_t {};

  constexpr nullopt_t nullopt;

  template<class T>
  struct optional {
    union {
      T val;
    };
    bool has = false;

    optional() {}
    optional(nullopt_t) {}
    optional(T const& val): val(val), has(true) {}

    T& operator*() {
      return val;
    }
    T* operator->() {
      return &val;
    }
  };

  template<class T>
  bool operator==(optional<T> const& a, optional<T> const& b) {
    return (!a.has && !b.has) || (a.bas && b.has && a.val == b.val);
  }
  template<class T>
  bool operator==(optional<T> const& opt, nullopt_t) {
    return !opt.has;
  }

  template<class T>
  bool operator!=(optional<T> const& a, optional<T> const& b) {
    return !(a == b);
  }
  template<class T>
  bool operator!=(optional<T> const& a, nullopt_t b) {
    return !(a == b);
  }
}

#elif __cplusplus < 201703L
# include <experimental/optional>
namespace std {
  using experimental::nullopt;
  using experimental::optional;
}

#else
# include <optional>
#endif
