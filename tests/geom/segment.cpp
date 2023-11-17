#include "geom/segment.hpp"
#include "iostream.hpp"

int main() {
  while(cin) {
    int n;
    cin >> n;
    vector<Segment<ll>> segs(n);
    cin >> segs;

    for(auto i: v::iota(0, n)) {
      auto a = segs[i];
      for(auto b: segs | v::drop(i + 1)) {
        auto result = a.intersection(b);
        if(result) {
          cout << *result << endl;
        }
      }
    }
  }
}
