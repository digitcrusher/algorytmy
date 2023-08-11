#include "geom/pick.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    Polygon<ll> poly;
    poly.pts.resize(n);
    cin >> poly.pts;

    auto result = pick(poly, poly.area() * 2);
    cout << result.insidec << " " << result.on_edgec << endl;
  }
}
