#include "graph/knights_tour.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int w, h, x, y;
    cin >> w >> h >> x >> y;
    x--, y--;

    auto result = knights_tour(w, h, x, y);
    if(result) {
      for(auto &row: *result) {
        for(auto cell: row) {
          cout << cell + 1 << " ";
        }
        cout << endl;
      }
    } else {
      cout << "nullopt" << endl;
    }
  }
}
