#include "ds/prefix_sums_2d.hpp"
#include <iostream>

int main() {
  int w, h;
  cin >> w >> h;
  vector nums(h, vector<int>(w));
  for(auto &row: nums) {
    for(auto &num: row) {
      cin >> num;
    }
  }

  PrefixSums2D<int, plus<int>, minus<int>> prefix_sums(nums);

  while(true) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if(!cin) break;
    x1--, y1--, x2--, y2--;
    cout << prefix_sums.get(x1, y1, x2, y2) << endl;
  }
}
