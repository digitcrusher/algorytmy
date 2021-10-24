#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
# pragma GCC diagnostic warning "-Wall"
# pragma GCC diagnostic warning "-Wextra"
# pragma GCC diagnostic warning "-Wformat=2"
# pragma GCC diagnostic warning "-Wnull-dereference"
# pragma GCC diagnostic warning "-Wduplicated-branches"
# pragma GCC diagnostic warning "-Wduplicated-cond"
# pragma GCC diagnostic warning "-Wfloat-equal"
# pragma GCC diagnostic warning "-Wshadow"
# pragma GCC diagnostic warning "-Wconversion"
# pragma GCC diagnostic warning "-Wlogical-op"
# pragma GCC diagnostic warning "-Wvector-operation-performance"
# pragma GCC diagnostic warning "-Wdisabled-optimization"
# pragma GCC diagnostic warning "-Wunsafe-loop-optimizations"
# pragma GCC diagnostic warning "-Wdouble-promotion"
#endif
#pragma GCC target "arch=ivybridge", "tune=ivybridge"
#if defined(ONLINE_JUDGE) || !defined(__OPTIMIZE__)
# pragma GCC optimize "Ofast", "inline", "unroll-loops", "ipa-pta", "no-rtti", \
  "no-exceptions", "nothrow-opt", "strict-enums", "stdarg-opt", "tracer"
# pragma GCC target "inline-all-stringops"
#endif
// NOTE: This is a multiline statement, so you have to enclose it in a code block.
#define rep(var, begin, end, step) \
  auto const _##var##_begin = (begin); \
  auto const _##var##_end = (end); \
  auto const _##var##_step = (step); \
  bool const _##var##_is_rev = _##var##_end < _##var##_begin; \
  assert(_##var##_step >= 0); \
  for( \
    auto var = _##var##_begin; \
    _##var##_is_rev ? var >= _##var##_end : var <= _##var##_end; \
    _##var##_is_rev ? var -= _##var##_step : var += _##var##_step \
  )
#define rangeof(c) (c).begin(), (c).end()

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

}
