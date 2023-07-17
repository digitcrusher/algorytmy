#include "graph/knights_tour.hpp"
#include <iostream>

int main() {
  while(true) {
    int w, h, x, y;
    cin >> w >> h >> x >> y;
    if(!cin) break;
    x--, y--;

    auto result = knights_tour(w, h, x, y);
    if(result == nullopt) {
      cout << "nullopt" << endl;
    } else {
      for(auto &row: *result) {
        for(auto cell: row) {
          cout << cell + 1 << " ";
        }
        cout << endl;
      }
    }
  }
}
