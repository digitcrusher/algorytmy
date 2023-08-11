#include "geom/convex_hull.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    vector<Point<ll>> pts(n);
    cin >> pts;

    cout << convex_hull(pts).pts;
  }
}
