#include "geom/closest_pair.hpp"
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

    auto [a1, b1] = closest_pair_sweep(pts);
    cout << (a1 - b1).mag() << endl;
    cout << a1.x << " " << a1.y << endl;
    cout << b1.x << " " << b1.y << endl;

    auto [a2, b2] = closest_pair_conquer(pts);
    cout << (a2 - b2).mag() << endl;
    cout << a2.x << " " << a2.y << endl;
    cout << b2.x << " " << b2.y << endl;

    assert((a1 - b1).mag() == (a2 - b2).mag());
  }
}
