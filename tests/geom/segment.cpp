#include "geom/segment.hpp"
#include <iostream>
#include <vector>

int main() {
  while(true) {
    int n;
    cin >> n;
    if(!cin) break;
    vector<Segment<ll>> segs(n);
    for(auto &[a, b]: segs) {
      cin >> a.x >> a.y >> b.x >> b.y;
      if(!cin) break;
    }
    if(!cin) break;

    for(int i = 0; i < n; i++) {
      for(int j = i + 1; j < n; j++) {
        auto result = segs[i].intersection(segs[j]);
        if(result) {
          cout << result->x << " " << result->y << endl;
        }
      }
    }
  }
}
