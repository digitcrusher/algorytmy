/*
 * Kompatybilnościowa implementacja <optional> z C++17 - digitcrusher/algorytmy
 *
 * Copyright (C) 2021-2022 Karol "digitcrusher" Łacina
 *
 * Copying and distribution of this software, with or without modification,
 * are permitted in any medium without royalty. This software is offered
 * as-is, without any warranty.
 */
#pragma once

#if __cplusplus < 201402L
namespace std {
  struct nullopt_t {};

  constexpr nullopt_t nullopt;

  template<class A>
  struct optional {
    union {
      A val;
    };
    bool has = false;

    optional() {}
    optional(nullopt_t) {}
    optional(A const& val): val(val), has(true) {}

    A& operator*() {
      return val;
    }
    A* operator->() {
      return &val;
    }
    operator bool() {
      return has;
    }
  };

  template<class A>
  bool operator==(optional<A> const& a, optional<A> const& b) {
    return (!a.has && !b.has) || (a.bas && b.has && a.val == b.val);
  }
  template<class A>
  bool operator==(optional<A> const& opt, nullopt_t) {
    return !opt.has;
  }

  template<class A>
  bool operator!=(optional<A> const& a, optional<A> const& b) {
    return !(a == b);
  }
  template<class A>
  bool operator!=(optional<A> const& a, nullopt_t b) {
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
