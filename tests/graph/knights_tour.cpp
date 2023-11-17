#include "graph/knights_tour.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int w, h, x, y;
    cin >> w >> h >> x >> y;
    x--, y--;

    auto result = knights_tour(w, h, x, y);
    if(result) {
      for(auto &i: *result) {
        cout << (i | v::transform(λ(_ + 1))) << endl;
      }
    } else {
      cout << "nullopt" << endl;
    }
  }
}
