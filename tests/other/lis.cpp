#include "other/lis.hpp"
#include <iostream>

int main() {
  while(true) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for(auto &i: nums) {
      cin >> i;
    }
    if(!cin) break;

    auto result = lis(nums);
    for(auto i: result) {
      cout << nums[i] << " ";
    }
    cout << endl;
    assert(result == lis_segtree(nums));
  }
}
