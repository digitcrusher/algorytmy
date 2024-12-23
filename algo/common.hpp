#pragma once

#include <algorithm>
#include <cassert>
#include <climits>
#include <numeric>
#include <ranges>
#include <vector>

using namespace std;
namespace r = ranges;
namespace v = views;

#define λ(expr) ([&](auto const& _) { return (expr); }) // <Ctrl+Shift+U>3BB<Space>
#define λ2(expr) ([&](auto const& _1, auto const& _2) { return (expr); })
template<class F>
struct Y {
  F f;
  decltype(auto) operator()(auto &&...args) const {
    return f(*this, forward<decltype(args)>(args)...);
  }
};

using i128 = __int128_t;
using ld = long double;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
