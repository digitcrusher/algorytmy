#include "geom/convex_hull.hpp"
#include <iostream>

int main() {
  while(true) {
    int n;
    cin >> n;
    if(!cin) break;
    vector<Point<ll>> pts(n);
    for(auto &[x, y]: pts) {
      cin >> x >> y;
      if(!cin) break;
    }
    if(!cin) break;

    auto result = convex_hull(pts);
    for(auto [x, y]: result.pts) {
      cout << x << " " << y << endl;
    }
  }
}
