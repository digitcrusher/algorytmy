#pragma once

// Wyłącza asserty - funkcje wywołujące błąd, gdy dany warunek jest fałszywy.
//#define NDEBUG
#include <cassert>

// Pomocnicze deklaracje znacznie skracające długość kodu
using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#include <ranges>

using namespace std;
namespace r = ranges;
namespace v = r::views;

#define λ(expr) ([&](auto const& _) { return (expr); }) // <Ctrl+Shift+U>3BB<Space>
#define λ2(expr) ([&](auto const& _1, auto const& _2) { return (expr); })
template<class F>
struct Y {
  F f;
  decltype(auto) operator()(auto &&...args) const {
    return f(*this, forward<decltype(args)>(args)...);
  }
};
