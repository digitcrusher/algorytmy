#include "geom/segment.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    vector<Segment<ll>> segs(n);
    cin >> segs;

    for(int i = 0; i < n; i++) {
      for(int j = i + 1; j < n; j++) {
        auto result = segs[i].intersection(segs[j]);
        if(result) {
          cout << *result << endl;
        }
      }
    }
  }
}
