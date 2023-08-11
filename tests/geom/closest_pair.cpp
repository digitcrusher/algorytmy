#include "geom/closest_pair.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    vector<Point<ll>> pts(n);
    cin >> pts;

    auto [a1, b1] = closest_pair_sweep(pts);
    cout << (a1 - b1).mag() << endl;
    cout << a1 << endl;
    cout << b1 << endl;

    auto [a2, b2] = closest_pair_conquer(pts);
    cout << (a2 - b2).mag() << endl;
    cout << a2 << endl;
    cout << b2 << endl;

    assert((a1 - b1).mag() == (a2 - b2).mag());
  }
}
