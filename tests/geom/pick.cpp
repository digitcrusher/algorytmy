#include "geom/pick.hpp"
#include <iostream>

int main() {
  while(true) {
    int n;
    cin >> n;
    if(!cin) break;
    Polygon<ll> poly;
    poly.pts.resize(n);
    for(auto &[x, y]: poly.pts) {
      cin >> x >> y;
      if(!cin) break;
    }
    if(!cin) break;

    auto [insidec, on_edgec] = pick(poly, poly.area() * 2);
    cout << insidec << " " << on_edgec << endl;
  }
}
