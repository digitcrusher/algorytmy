#include <bits/stdc++.h>

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

}
