#include "geom/convex_hull_trick.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;
  vector<Point<ll>> funcs(n);
  for(auto &[a, b]: funcs) {
    cin >> a >> b;
  }

  ConvexHullTrick trick(funcs);

  while(true) {
    ll x;
    cin >> x;
    if(!cin) break;

    cout << trick.get(x) << endl;
  }
}
