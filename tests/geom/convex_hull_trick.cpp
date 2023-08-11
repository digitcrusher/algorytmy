#include "geom/convex_hull_trick.hpp"
#include "iostream.hpp"

int main() {
  int n;
  cin >> n;
  vector<Point<ll>> funcs(n);
  for(auto &[a, b]: funcs) {
    cin >> a >> b;
  }

  ConvexHullTrick trick(funcs);

  while(cin) {
    ll x;
    cin >> x;

    cout << trick.get(x) << endl;
  }
}
