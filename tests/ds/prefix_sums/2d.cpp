#include "ds/prefix_sums/2d.hpp"
#include "iostream.hpp"

int main() {
  int w, h;
  cin >> w >> h;
  vector nums(h, vector<ll>(w));
  cin >> nums;

  PrefixSums2D<ll, plus<>, minus<>> prefix_sums(nums);

  while(cin) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1--, y1--, x2--, y2--;

    cout << prefix_sums.get(x1, y1, x2, y2) << endl;
  }
}
