#include "ds/prefix_sums.hpp"
#include <iostream>

int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for(auto &num: nums) {
    cin >> num;
  }

  PrefixSums<int, plus<int>, minus<int>> prefix_sums(nums);

  while(true) {
    int a, b;
    cin >> a >> b;
    if(!cin) break;
    a--, b--;
    cout << prefix_sums.get(a, b) << endl;
  }
}
